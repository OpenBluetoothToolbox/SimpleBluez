include(FetchContent)

if (SIMPLEDBUS_VENDORIZE)

    # Load default parameters passed in through the command line.
    if(NOT SIMPLEDBUS_GIT_REPOSITORY)
        set(SIMPLEDBUS_GIT_REPOSITORY "https://github.com/OpenBluetoothToolbox/SimpleDBus.git")
    endif()
    if(NOT SIMPLEDBUS_GIT_TAG)
        set(SIMPLEDBUS_GIT_TAG "feature/next")
    endif()

    if(NOT SIMPLEDBUS_LOCAL_PATH)
        FetchContent_Declare(
            simpledbus
            GIT_REPOSITORY ${SIMPLEDBUS_GIT_REPOSITORY}
            GIT_TAG ${SIMPLEDBUS_GIT_TAG}
            GIT_SHALLOW YES
        )

        # Note that here we manually do what FetchContent_MakeAvailable() would do,
        # except to ensure that the dependency can also get what it needs, we add
        # custom logic between the FetchContent_Populate() and add_subdirectory()
        # calls.
        FetchContent_GetProperties(simpledbus)
        if(NOT simpledbus_POPULATED)
            FetchContent_Populate(simpledbus)
            list(APPEND CMAKE_MODULE_PATH "${simpledbus_SOURCE_DIR}/cmake/find")

            # If vendorizing SimpleDBus, it should always be built as a static library.
            set(BUILD_SHARED_LIBS_SAVED "${BUILD_SHARED_LIBS}")
            set(BUILD_SHARED_LIBS OFF)
            add_subdirectory(${simpledbus_SOURCE_DIR} ${simpledbus_BINARY_DIR})
            set(BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS_SAVED}")
        endif()

    else()
        list(APPEND CMAKE_MODULE_PATH "${SIMPLEDBUS_LOCAL_PATH}/cmake/find")
        add_subdirectory(${SIMPLEDBUS_LOCAL_PATH} ${CMAKE_CURRENT_BINARY_DIR}/simpledbus)
    endif()

    # Because we are in a find module, we are solely responsible for resolution.
    # Setting this *_FOUND variable to a truthy value will signal to the calling
    # find_package() command that we were successful.
    # More relevant info regarding find modules and what variables they use can be
    # found in the documentation of find_package() and
    # https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html
    set(simpledbus_FOUND 1)

else()

    find_package(simpledbus CONFIG REQUIRED)

endif()
