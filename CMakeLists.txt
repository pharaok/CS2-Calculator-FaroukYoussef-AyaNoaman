cmake_minimum_required(VERSION 3.10)

project(calculator)

add_library(bigint STATIC src/bigint.cpp)
add_library(parser STATIC src/parser.cpp)
target_link_libraries(parser bigint)

add_executable(test_bigint tests/bigint.cpp)
target_link_libraries(test_bigint bigint)
add_executable(test_calculator tests/calculator.cpp)
target_link_libraries(test_calculator bigint)
add_executable(test_parser tests/parser.cpp)
target_link_libraries(test_parser parser)




add_custom_target(test COMMAND test_bigint 
                       COMMAND test_calculator 
                       COMMAND test_parser)
add_custom_target(run COMMAND calculator)
