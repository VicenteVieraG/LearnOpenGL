# Main CMake file

#! CMake minimum version. Make that your current CMake version is greater than this
cmake_minimum_required(VERSION 4.0.3)

# Project name, version and languages
#! Change the project name and version here
project(LearOpenGL VERSION 0.0.1 LANGUAGES C CXX)

# Configure build options
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create binary outputs at ./build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Subdirectories
#! NOTE: The add_subdirectory order matters
add_subdirectory(config)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(app)
