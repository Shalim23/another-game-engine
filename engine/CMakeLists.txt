project(age-engine)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(SDL_SHARED OFF CACHE BOOL "Build SDL as a static library" FORCE)
FetchContent_Declare(SDL3
    URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.4.0.tar.gz
)

FetchContent_MakeAvailable(SDL3)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        "include/Engine.cppm"
    PRIVATE
        src/Engine.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
