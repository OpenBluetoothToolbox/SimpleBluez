cmake_minimum_required(VERSION 3.16.0)

project(EXAMPLE_LIST_PAIRED)

message("-- [INFO] Building Example")
add_executable(example_list_paired list_paired.cpp)
target_link_libraries(example_list_paired simplebluez-static)
