cmake_minimum_required(VERSION 3.9)
project(cpptools)

# Project attributes and env vars.
set(CMAKE_CXX_STANDARD 11)
set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(SRCEXT cc)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/cmake)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/cmake)

# Includes
include_directories(${COMMON_INCLUDES})

# Gather (non-main) source files.
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.${SRCEXT})
list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.${SRCEXT})

# Main executable - link in project libraries.
add_executable(main ${PROJECT_SOURCE_DIR}/src/main.${SRCEXT})

# Configure unit tests to work with googletest.
add_subdirectory(vendor/googletest ${CMAKE_SOURCE_DIR}/build/cmake/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Gather test files
#file(GLOB_RECURSE TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.${SRCEXT})
add_executable(test_all
        ${PROJECT_SOURCE_DIR}/test/test_all.${SRCEXT})
add_executable(linkedlist_test
        ${PROJECT_SOURCE_DIR}/test/linkedlist/linkedlist_test.${SRCEXT})
add_executable(sort_test
        ${PROJECT_SOURCE_DIR}/test/sort/sort_test.${SRCEXT})
target_link_libraries(test_all gtest gtest_main)
target_link_libraries(linkedlist_test gtest gtest_main)
target_link_libraries(sort_test gtest gtest_main)
