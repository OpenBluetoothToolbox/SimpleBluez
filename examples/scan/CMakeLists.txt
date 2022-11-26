cmake_minimum_required(VERSION 3.16.0)

project(EXAMPLE_SCAN)

if (CONAN_BUILD)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

message("-- [INFO] Building Example")
add_executable(example_scan scan.cpp)
target_link_libraries(example_scan simplebluez-static ${CONAN_LIBS})
