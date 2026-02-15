project(age-demo)

file(GLOB_RECURSE DEMO_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${DEMO_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE age-engine)
