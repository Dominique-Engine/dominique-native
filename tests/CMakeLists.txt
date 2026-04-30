cmake_minimum_required(VERSION 3.14)

include_directories("../src")

add_executable(ecs_tests
        test_support.cpp
        test_ecs.cpp
        "../src/dengine/utils/uuid.cpp"
)

target_include_directories(ecs_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(ecs_tests PRIVATE Dominique)

# Register the test with CTest. The executable itself acts as the test runner.
add_test(NAME ecs_tests COMMAND ecs_tests)
