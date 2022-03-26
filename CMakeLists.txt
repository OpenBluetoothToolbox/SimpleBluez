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
    
    # Nice hack to automatically ignore the build directory
    file(WRITE ${CMAKE_BINARY_DIR}/.gitignore "*")
else()
    set(STANDALONE false)
endif()

# Append additional flags for address and thread sanitization
if(SIMPLEBLUEZ_SANITIZE MATCHES "Address")
    set(SIMPLEDBUS_SANITIZE ${SIMPLEBLUEZ_SANITIZE})
    set(EXTRA_COMPILE_OPTIONS ${EXTRA_COMPILE_OPTIONS} -fsanitize=address -fsanitize-recover=address -fno-omit-frame-pointer -fno-common -g)
    set(EXTRA_LINK_OPTIONS ${EXTRA_LINK_OPTIONS} -fsanitize=address)
endif()

if(SIMPLEBLUEZ_SANITIZE MATCHES "Thread")
    set(SIMPLEDBUS_SANITIZE ${SIMPLEBLUEZ_SANITIZE})
    set(EXTRA_COMPILE_OPTIONS ${EXTRA_COMPILE_OPTIONS} -fsanitize=thread -fno-omit-frame-pointer -fno-common -g)
    set(EXTRA_LINK_OPTIONS ${EXTRA_LINK_OPTIONS} -fsanitize=thread)
endif()

# Load default parameters passed in through the command line.
if(NOT SIMPLEDBUS_GIT_REPOSITORY)
    set(SIMPLEDBUS_GIT_REPOSITORY "https://github.com/OpenBluetoothToolbox/SimpleDBus.git")
endif()
if(NOT SIMPLEDBUS_GIT_TAG)
    set(SIMPLEDBUS_GIT_TAG "v2.1.0")
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

# Load default parameters passed in through the command line.
if(NOT LIBFMT_GIT_REPOSITORY)
    set(LIBFMT_GIT_REPOSITORY "https://github.com/fmtlib/fmt.git")
endif()
if(NOT LIBFMT_GIT_TAG)
    set(LIBFMT_GIT_TAG "d141cdbeb0fb422a3fb7173b285fd38e0d1772dc") # v8.0.1
endif()

if(NOT LIBFMT_LOCAL_PATH)
    # Library includes
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY ${LIBFMT_GIT_REPOSITORY}
        GIT_TAG ${LIBFMT_GIT_TAG}
    )
    FetchContent_MakeAvailable(fmt)
else()
    message("-- [INFO] Using local LibFmt")
    add_subdirectory(${LIBFMT_LOCAL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/libfmt)
endif()

include_directories(${SIMPLEDBUS_INCLUDES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/legacy)

message("-- [INFO] Building SimpleBluez")
file(GLOB_RECURSE SRC_simplebluez_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(simplebluez-static STATIC ${SRC_simplebluez_FILES})
add_library(simplebluez SHARED ${SRC_simplebluez_FILES})

target_compile_options(simplebluez-static PRIVATE -std=c++17 -fPIC -Wfatal-errors -Wpedantic -O3 -Og ${EXTRA_COMPILE_OPTIONS})
target_compile_options(simplebluez PRIVATE -std=c++17 -fPIC -Wfatal-errors -Wpedantic -O3 -Og ${EXTRA_COMPILE_OPTIONS})

target_link_libraries(simplebluez-static PUBLIC simpledbus-static pthread ${EXTRA_LINK_OPTIONS})
target_link_libraries(simplebluez PUBLIC simpledbus-static pthread ${EXTRA_LINK_OPTIONS})

target_link_libraries(simplebluez-static PRIVATE fmt::fmt-header-only)
target_link_libraries(simplebluez PRIVATE fmt::fmt-header-only)

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
