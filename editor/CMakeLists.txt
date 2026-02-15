project(age-editor)

add_subdirectory("${CMAKE_SOURCE_DIR}/deps/_deps/pybind11-src" "${CMAKE_SOURCE_DIR}/deps/_deps/pybind11-build")

pybind11_add_module(${PROJECT_NAME} SHARED src/bindings.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE age-engine)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    SUFFIX ".pyd"
    OUTPUT_NAME "age-editor"
)
