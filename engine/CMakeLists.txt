cmake_minimum_required(VERSION 4.0)

# libstdc++'s `import std` support needs GCC 15+, unavailable on Ubuntu24,
# so we use libc++ instead. The libc++-23-dev package's own modules.json ships
# a relative path that's only correct from its /usr/lib/llvm-23/lib symlink,
# not from the real file clang resolves by default, hence the explicit override.
set(CMAKE_CXX_FLAGS "-stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "-stdlib=libc++")
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
set(CMAKE_CXX_STDLIB_MODULES_JSON "/usr/lib/llvm-23/lib/libc++.modules.json")

project(engine CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
  message(FATAL_ERROR "Ninja is required as cmake generator")
endif()

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR
  CMAKE_CXX_COMPILER_VERSION VERSION_LESS "23")
  message(FATAL_ERROR "At least clang++-23 is required")
endif()

#TODO add_library once demo is implemented
add_executable(${PROJECT_NAME} "src/main.cpp")

target_sources(${PROJECT_NAME} PUBLIC
  FILE_SET CXX_MODULES
    FILES
      "src/engine.cppm")

target_sources(${PROJECT_NAME} PRIVATE
  "src/engine.cpp")
