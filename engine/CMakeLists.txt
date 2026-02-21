project(age-engine)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/deps/_deps/sdl3-build")
find_package(SDL3 REQUIRED CONFIG)

file(GLOB_RECURSE PRIVATE_SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} ${PRIVATE_SOURCES})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
