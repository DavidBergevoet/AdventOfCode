cmake_minimum_required(VERSION 3.10)


add_library(Matrix INTERFACE)
target_include_directories(Matrix INTERFACE 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)