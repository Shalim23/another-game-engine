project(age-editor)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(pybind11
    URL https://github.com/pybind/pybind11/archive/refs/tags/v2.13.4.tar.gz
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(${PROJECT_NAME} SHARED src/bindings.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE age-engine)

set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
