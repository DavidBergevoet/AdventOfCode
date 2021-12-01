cmake_minimum_required(VERSION 3.10)

add_library(FileHandler FileHandler.cpp)

target_include_directories (FileHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})