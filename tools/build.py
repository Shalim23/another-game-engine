import subprocess
from pathlib import Path

ROOT_DIR = Path(__file__).resolve().parent.parent
BUILD_DIR = ROOT_DIR / "build"
ENGINE_DIR = str(ROOT_DIR / "engine")
ENGINE_BUILD_DIR = str(BUILD_DIR / "engine")

subprocess.check_call(
    ["cmake", "-S", 
     ENGINE_DIR, "-B", ENGINE_BUILD_DIR,
     "-G", "Ninja", 
     "-DCMAKE_CXX_COMPILER=clang++-23",
     "-DCMAKE_C_COMPILER=clang-23"])

subprocess.check_call(["cmake", "--build", ENGINE_BUILD_DIR])
