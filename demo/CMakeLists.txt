project(age-demo)

file(GLOB_RECURSE DEMO_MODULES "*.cppm")
file(GLOB_RECURSE DEMO_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${DEMO_SOURCES})

target_sources(${PROJECT_NAME}
    PUBLIC FILE_SET CXX_MODULES FILES
        ${DEMO_MODULES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE age-engine)
