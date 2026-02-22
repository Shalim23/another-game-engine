project(age-engine)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/deps/_deps/sdl3-build")
find_package(SDL3 REQUIRED CONFIG)

file(GLOB_RECURSE PRIVATE_SOURCES "src/*.cpp")
file(GLOB_RECURSE MODULE_SOURCES "src/*.ixx")

add_library(${PROJECT_NAME} ${PRIVATE_SOURCES})

target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        ${MODULE_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
