cmake_minimum_required(VERSION 3.16.0)

project(EXAMPLE_READ)

message("-- [INFO] Building Example")
add_executable(example_read read.cpp)
target_link_libraries(example_read simplebluez-static)
