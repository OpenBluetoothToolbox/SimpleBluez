cmake_minimum_required(VERSION 3.16.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(SimpleBluez VERSION 0.1 LANGUAGES CXX)

# Include all necessary CMake modules
include(FetchContent)

# Detect if the project is being build within a project or standalone.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(STANDALONE true)

    # Configure the build path
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
else()
    set(STANDALONE false)
endif()

# Load default parameters passed in through the command line.
if(NOT SIMPLEDBUS_GIT_REPOSITORY)
    set(SIMPLEDBUS_GIT_REPOSITORY "https://github.com/OpenBluetoothToolbox/SimpleDBus.git")
endif()
if(NOT SIMPLEDBUS_GIT_TAG)
    set(SIMPLEDBUS_GIT_TAG "feature/proxy")
endif()

if(NOT SIMPLEDBUS_LOCAL_PATH)
    # Library includes
    FetchContent_Declare(
        simpledbus
        GIT_REPOSITORY ${SIMPLEDBUS_GIT_REPOSITORY}
        GIT_TAG ${SIMPLEDBUS_GIT_TAG}
    )
    FetchContent_MakeAvailable(simpledbus)
else()
    message("-- [INFO] Using local SimpleDBus")
    add_subdirectory(${SIMPLEDBUS_LOCAL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/simpledbus)
endif()

include_directories(${SIMPLEDBUS_INCLUDES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

message("-- [INFO] Building SimpleBluez")
file(GLOB_RECURSE SRC_simplebluez_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(simplebluez-static STATIC ${SRC_simplebluez_FILES})
add_library(simplebluez SHARED ${SRC_simplebluez_FILES})

target_compile_options(simplebluez-static PRIVATE -std=c++17 -fPIC -Wfatal-errors -Wpedantic -O3)
target_compile_options(simplebluez PRIVATE -std=c++17 -fPIC -Wfatal-errors -Wpedantic -O3)

target_link_libraries(simplebluez-static PUBLIC simpledbus-static)
target_link_libraries(simplebluez PUBLIC simpledbus-static)

# Export the variables needed by the parent project
if(NOT ${STANDALONE})
    set(SIMPLEBLUEZ_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src ${SIMPLEDBUS_INCLUDES} PARENT_SCOPE)
endif()
