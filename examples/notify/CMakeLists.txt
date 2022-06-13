cmake_minimum_required(VERSION 3.16.0)

project(EXAMPLE_NOTIFY)

if (CONAN_BUILD)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

message("-- [INFO] Building Example")
add_executable(example_notify notify.cpp)
target_link_libraries(example_notify simplebluez-static ${CONAN_LIBS})
