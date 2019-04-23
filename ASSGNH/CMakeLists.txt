set(NAME "my_project")

cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)

# Project information
project(${NAME})
set(VERION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# Environment Information
include_directories(${PROJECT_SOURCE_DIR}/inc)
#link_directories(${PROJECT_SOURCE_DIR}/external/lib)
add_executable(${NAME} ${PROJECT_SOURCE_DIR}/src/test_yourString.cpp)