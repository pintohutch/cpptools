# Specify the minimum version for CMake
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Project's name
PROJECT(cpp-tools)

# Set the output folder where your program will be created
SET(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# The following folder will be included
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}")
