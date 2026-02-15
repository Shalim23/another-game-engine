project(age-engine)

if(WIN32)
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/deps/_deps/sdl3-build")
    find_package(SDL3 REQUIRED CONFIG)
else()
    #TODO: Add support for other platforms
    message(FATAL_ERROR "This project is only supported on Windows.")
endif()

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        "include/Engine.cppm"
    PRIVATE
        src/Engine.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
