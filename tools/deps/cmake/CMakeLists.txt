cmake_minimum_required(VERSION 4.0)
project(another-game-engine-deps)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(SDL_SHARED OFF CACHE BOOL "Build SDL as a static library" FORCE)
FetchContent_Declare(SDL3
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.4.0.tar.gz
)

FetchContent_MakeAvailable(SDL3)


FetchContent_Declare(pybind11
    URL https://github.com/pybind/pybind11/archive/refs/tags/v2.13.4.tar.gz
)
FetchContent_MakeAvailable(pybind11)
