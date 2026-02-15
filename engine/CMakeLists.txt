project(age-engine)

if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/deps/_deps/sdl3-build")
    find_package(SDL3 REQUIRED CONFIG)
else()
    #TODO: Add support for other platforms
    message(FATAL_ERROR "This project is only supported on Windows.")
endif()

file(GLOB_RECURSE PUBLIC_MODULES "include/*.cppm")
file(GLOB_RECURSE INTERNAL_MODULES "src/*.cppm")
file(GLOB_RECURSE PRIVATE_SOURCES "src/*.cpp")

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        ${PUBLIC_MODULES}
    PRIVATE FILE_SET cxx_internal_modules TYPE CXX_MODULES FILES
        ${INTERNAL_MODULES}
    PRIVATE
        ${PRIVATE_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
