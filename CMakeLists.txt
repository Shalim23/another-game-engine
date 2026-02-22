cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -fmodule-file=std=${CMAKE_SOURCE_DIR}/deps/std.pcm")

project(another-game-engine)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 20)
        message(STATUS "Clang 20 or newer detected.")
    else()
        message(WARNING "Clang 20 or newer is required. You are using Clang ${CMAKE_CXX_COMPILER_VERSION}.")
    endif()
else()
    message(WARNING "Clang 20 or newer is required. Detected compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}.")
endif()

project(another-game-engine)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(CMAKE_BUILD_TYPE "Build type" Debug)

find_package(Python3 REQUIRED)
execute_process(
    COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/tools/deps/build_deps.py"
    RESULT_VARIABLE SCRIPT_RESULT
)

if(NOT SCRIPT_RESULT EQUAL 0)
    message(FATAL_ERROR "build_deps.py script failed with exit code ${SCRIPT_RESULT}")
endif()

add_subdirectory(engine)
add_subdirectory(editor)
add_subdirectory(demo)
