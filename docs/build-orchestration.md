# Build Orchestration

## Entry point

- `tools/build.py` is the build driver — not a top-level CMake superbuild.
  It shells out to CMake for each project (`engine`, `demo`) rather than
  CMake invoking itself via `ExternalProject_Add`.
- Rebuilding always re-invokes `cmake --build` on `engine`; CMake/Ninja's
  own incremental build makes an unchanged rebuild a fast no-op, so the
  script doesn't need separate staleness-tracking logic.

## Engine variants

- `engine` is built and installed twice, into separate install trees:
  - editor-enabled (`-DWITH_EDITOR=ON`)
  - standalone (`-DWITH_EDITOR=OFF`)
- `demo` links against whichever installed variant its build configuration
  targets, via `CMAKE_PREFIX_PATH`. Editor and standalone are separate
  `demo` build configurations, not one build linking both.

## Shipping engine binaries

- `engine/CMakeLists.txt` declares every module interface unit (and
  interface partition) in one `FILE_SET CXX_MODULES` list, independent of
  where the files live in the source tree.
- `install(TARGETS engine EXPORT engineTargets FILE_SET CXX_MODULES ...)`
  copies those interface files into the install tree alongside the
  compiled library.
- `install(EXPORT engineTargets ...)` generates the CMake package config
  that `demo`'s `find_package(engine)` uses.
- What ships is the compiled library binary plus module interface
  *source* — not the precompiled BMI (`.pcm`), which isn't a portable
  artifact across compiler invocations. `demo`'s own build compiles the
  installed interface files into its own local BMI before linking against
  the prebuilt library.
- Interface units are listed explicitly in `FILE_SET`, not collected via
  `GLOB` — glob results are cached at CMake configure time, so a new
  module file added later wouldn't be picked up without a forced
  reconfigure.
- Same rule for implementation sources: `target_sources` lists files
  explicitly, no `GLOB`/`GLOB_RECURSE`, even with `CONFIGURE_DEPENDS`. This
  matters more than usual here since `FILE_SET CXX_MODULES` is also what
  gets installed/exported as engine's public API surface — an accidental
  glob inclusion ships something unintended, and a missed file breaks the
  install silently.
