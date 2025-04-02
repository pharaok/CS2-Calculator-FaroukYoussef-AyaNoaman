cmake_minimum_required(VERSION 3.10)

project(calculator)

add_library(bigint STATIC src/bigint.cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} bigint)

add_executable(test_bigint tests/bigint.cpp)
target_link_libraries(test_bigint bigint)

add_custom_target(test COMMAND test_bigint)
add_custom_target(run COMMAND calculator)
