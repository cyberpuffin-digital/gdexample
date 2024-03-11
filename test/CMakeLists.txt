cmake_minimum_required(VERSION 3.18)
project(gdexample_test VERSION 0.0.1 LANGUAGES CXX)

##### Setup Doctest #####
# Pull in doctest repository.  Useful for pulling in documentation and updates.
include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    doctest
    PREFIX ${CMAKE_BINARY_DIR}/doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

# Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")

# Add doctest globally
include_directories(${DOCTEST_INCLUDE_DIR})

##### Setup Godot CPP #####
set(godot_cpp_DIR ${CMAKE_SOURCE_DIR}/../godot-cpp)

# Verify library files exist
find_file(godot_cpp_x86_32_library
        NAMES libgodot-cpp.linux.template_debug.x86_32.a
        PATHS ${godot_cpp_DIR}/bin)

find_file(godot_cpp_x86_64_library
        NAMES libgodot-cpp.linux.template_debug.x86_64.a
        PATHS ${godot_cpp_DIR}/bin)

if (NOT EXISTS godot_cpp_x86_32_library AND NOT EXISTS godot_cpp_x86_64_library)
    message(WARNING "Godot CPP libraries not found.  Build Godot CPP first.")
endif()

include_directories(${godot_cpp_DIR}/gdextension/)
include_directories(${godot_cpp_DIR}/gen/include)
include_directories(${godot_cpp_DIR}/include)

##### Setup GDExample #####
# Check library files exist
if (UNIX)
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        find_library(GDExample_LIBRARY
            NAMES libgdexample.linux.template_debug.x86_32.so
            PATHS ${CMAKE_SOURCE_DIR}/../bin/linux
        )
    else()
    find_library(GDExample_LIBRARY
            NAMES libgdexample.linux.template_debug.x86_64.so
            PATHS ${CMAKE_SOURCE_DIR}/../bin/linux
        )
    endif()
elseif (WIN32)
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        find_library(GDExample_LIBRARY
            NAMES libgdexample.windows.template_debug.x86_32.dll
            PATHS ${CMAKE_SOURCE_DIR}/../bin/windows
        )
    else()
        find_library(GDExample_LIBRARY
            NAMES libgdexample.windows.template_debug.x86_64.dll
            PATHS ${CMAKE_SOURCE_DIR}/../bin/windows
        )
    endif()
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

# Include GDExample header files
include_directories(${CMAKE_SOURCE_DIR}/../src/)

if (NOT GDExample_LIBRARY)
    message(FATAL_ERROR "GDExample library was not found.  Build GDExample first.")
endif()

##### Build test binary #####
add_executable(gdexample_tests ${CMAKE_SOURCE_DIR}/src/test_gdexample.cpp)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        target_link_libraries(gdexample_tests PRIVATE ${godot_cpp_x86_32_library})
        message(STATUS "Linking Godot CPP x86_32")
    else()
        target_link_libraries(gdexample_tests PRIVATE ${godot_cpp_x_86_64_library})
        message(STATUS "Linking Godot CPP x86_64")
    endif()
else()
    # Add instructions for other platforms as needed
    message(WARNING "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

target_link_libraries(gdexample_tests PRIVATE ${GDExample_LIBRARY})

# Set working directory for tests
set_target_properties(gdexample_tests PROPERTIES CXX_STANDARD 17 WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src")

# Run tests on command line
add_custom_command(
    TARGET gdexample_tests
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Running tests..."
    COMMAND ${CMAKE_CTEST_COMMAND} --build-config $<CONFIG> --output-on-failure -C $<CONFIG>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
