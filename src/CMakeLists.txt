cmake_minimum_required(VERSION 3.10)

project(GameOfLife VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE MY_SOURCES 
    CONFIGURE_DEPENDS
    "*.cpp" 
    "*.hpp"
)

add_executable(GameOfLife ${MY_SOURCES})

target_include_directories(GameOfLife PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})