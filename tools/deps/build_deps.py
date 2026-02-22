import sys
import subprocess
from pathlib import Path


class DepsValidator:
    def __init__(self, build_dir: Path):
        self.build_dir = build_dir
        self.required_deps = ["_deps/sdl3-build", "_deps/pybind11-build", "std.pcm"]
        
    def check_deps_exist(self) -> bool:
        for dep in self.required_deps:
            dep_path = self.build_dir / dep
            if not dep_path.exists():
                print(f"Missing dependency: {dep}")
                return False

            if dep_path.is_dir():
                if not any(dep_path.iterdir()):
                    print(f"Dependency directory empty: {dep}")
                    return False

        return True


class DepsBuilder:
    def __init__(self,):
        self.build_dir = Path("deps")
        self.cmake_dir = Path("tools") / "deps" / "cmake"
        
    def __run_cmake_configure(self) -> bool:
        self.build_dir.mkdir(parents=True, exist_ok=True)
        
        try:
            result = subprocess.run(
                [
                    "cmake",
                    "-B", str(self.build_dir),
                    "-S", str(self.cmake_dir)
                ],
                capture_output=False,
                text=True
            )
            
            if result.returncode != 0:
                print("ERROR: cmake configure failed", file=sys.stderr)
                return False

            return True
            
        except FileNotFoundError:
            print("ERROR: cmake not found. Please install cmake.", file=sys.stderr)
            return False
        except Exception as e:
            print(f"ERROR: Failed to run cmake: {e}", file=sys.stderr)
            return False
    
    def __build_dependencies(self) -> bool:
        try:
            result = subprocess.run(
                ["cmake", "--build", str(self.build_dir)],
                capture_output=False,
                text=True
            )
            
            if result.returncode != 0:
                print(f"ERROR: cmake build failed", file=sys.stderr)
                return False
            
            if not Path("/usr/lib/llvm-20/share/libc++/v1/std.cppm").exists():
                print("ERROR: std.cppm not found. Please ensure libc++ is installed.", file=sys.stderr)
                return False
            
            subprocess.check_output([
                "clang",
                "-std=c++23", 
                "-stdlib=libc++", 
                "-Wno-reserved-module-identifier", 
                "--precompile", "-o", "deps/std.pcm", 
                "/usr/lib/llvm-20/share/libc++/v1/std.cppm"])

            return True
            
        except FileNotFoundError:
            print("ERROR: cmake not found. Please install cmake.", file=sys.stderr)
            return False
        except Exception as e:
            print(f"ERROR: Failed to build dependencies: {e}", file=sys.stderr)
            return False
    
    def build(self) -> bool:
        validator = DepsValidator(self.build_dir)
        if validator.check_deps_exist():
            return True
        
        if not self.__run_cmake_configure() or not self.__build_dependencies():
            return False
        
        if not validator.check_deps_exist():
            return False
        
        return True


def main():
    builder = DepsBuilder()
    if not builder.build():
        sys.exit(1)
    
    sys.exit(0)


if __name__ == "__main__":
    main()
