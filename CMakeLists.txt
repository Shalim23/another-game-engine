cmake_minimum_required(VERSION 4.0)
project(another-game-engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

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
