cmake_minimum_required(VERSION 3.16.0)

project(EXAMPLE_SCAN)

message("-- [INFO] Building Example")
add_executable(example_scan scan.cpp)
target_link_libraries(example_scan simplebluez-static)
