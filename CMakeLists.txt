cmake_minimum_required(VERSION 3.16.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/find")

project(SimpleBluez VERSION 0.1 LANGUAGES CXX)

if (CONAN_BUILD)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

option(LIBFMT_VENDORIZE "Enable vendorized libfmt" ON)
option(SIMPLEDBUS_VENDORIZE "Enable vendorized SimpleDBus" ON)

# Include all necessary CMake modules
include(FetchContent)

# Detect if the project is being build within a project or standalone.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(STANDALONE true)

    # Configure the build path
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    
    # Nice hack to automatically ignore the build directory
    file(WRITE ${CMAKE_BINARY_DIR}/.gitignore "*")
else()
    set(STANDALONE false)
endif()

set(SIMPLEDBUS_SANITIZE ${SIMPLEBLUEZ_SANITIZE})
find_package(simpledbus REQUIRED)
find_package(fmt REQUIRED)

if(NOT SIMPLEBLUEZ_LOG_LEVEL)
    set(SIMPLEBLUEZ_LOG_LEVEL "FATAL")
endif()

include_directories(${SIMPLEDBUS_INCLUDES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/legacy)

message(STATUS "Configuring SimpleBluez")
file(GLOB_RECURSE SRC_simplebluez_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(simplebluez-static STATIC ${SRC_simplebluez_FILES})
add_library(simplebluez SHARED ${SRC_simplebluez_FILES})

target_compile_definitions(simplebluez-static PRIVATE SIMPLEBLUEZ_LOG_LEVEL=${SIMPLEBLUEZ_LOG_LEVEL})
target_compile_definitions(simplebluez PRIVATE SIMPLEBLUEZ_LOG_LEVEL=${SIMPLEBLUEZ_LOG_LEVEL})

# Append additional flags for address and thread sanitization
if(SIMPLEBLUEZ_SANITIZE MATCHES "Address")
    set(EXTRA_COMPILE_OPTIONS ${EXTRA_COMPILE_OPTIONS} -fsanitize=address -fsanitize-recover=address -fno-omit-frame-pointer -fno-common -g)
    set(EXTRA_LINK_OPTIONS ${EXTRA_LINK_OPTIONS} -fsanitize=address)
elseif(SIMPLEBLUEZ_SANITIZE MATCHES "Thread")
    set(EXTRA_COMPILE_OPTIONS ${EXTRA_COMPILE_OPTIONS} -fsanitize=thread -fno-omit-frame-pointer -fno-common -g)
    set(EXTRA_LINK_OPTIONS ${EXTRA_LINK_OPTIONS} -fsanitize=thread)
endif()

target_compile_options(simplebluez-static PRIVATE -std=c++17 -fPIC -Wfatal-errors -Wpedantic -O3 -Og ${EXTRA_COMPILE_OPTIONS})
target_compile_options(simplebluez PRIVATE -std=c++17 -fPIC -Wfatal-errors -Wpedantic -O3 -Og ${EXTRA_COMPILE_OPTIONS})

target_link_libraries(simplebluez-static PUBLIC simpledbus-static pthread ${EXTRA_LINK_OPTIONS})
target_link_libraries(simplebluez PUBLIC simpledbus-static pthread ${EXTRA_LINK_OPTIONS})

target_link_libraries(simplebluez-static PRIVATE fmt::fmt-header-only)
target_link_libraries(simplebluez PRIVATE fmt::fmt-header-only)

if (CONAN_BUILD)
    add_subdirectory(examples)
endif()

# Export the variables needed by the parent project
if(NOT ${STANDALONE})
    set(
        SIMPLEBLUEZ_INCLUDES 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/legacy
        ${SIMPLEDBUS_INCLUDES}
        PARENT_SCOPE
        )
endif()
