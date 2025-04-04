cmake_minimum_required(VERSION 3.10)

project(calculator)

add_library(bigint STATIC src/bigint.cpp)

add_executable(test_bigint tests/bigint.cpp)
target_link_libraries(test_bigint bigint)

add_executable(test_calculator tests/calculator.cpp)
target_link_libraries(test_calculator bigint)

add_custom_target(test COMMAND test_bigint COMMAND test_calculator)
add_custom_target(run COMMAND calculator)
