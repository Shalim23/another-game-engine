project(age-engine)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/deps/_deps/sdl3-build")
find_package(SDL3 REQUIRED CONFIG)

file(GLOB_RECURSE PRIVATE_SOURCES "src/*.cpp")
file(GLOB_RECURSE PUBLIC_MODULE_SOURCES "include/*.ixx")
file(GLOB_RECURSE PRIVATE_MODULE_SOURCES "src/*.ixx")

add_library(${PROJECT_NAME} ${PRIVATE_SOURCES})

target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        ${PUBLIC_MODULE_SOURCES}
)
target_sources(${PROJECT_NAME}
    PRIVATE FILE_SET cxx_private_modules TYPE CXX_MODULES FILES
        ${PRIVATE_MODULE_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
