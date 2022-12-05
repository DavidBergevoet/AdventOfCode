cmake_minimum_required(VERSION 3.10)

project(AdventOfCode-2022-05) 

configure_file("input.txt" "input.txt" COPYONLY)

add_executable(${PROJECT_NAME}_Part1 part1.cpp)
target_link_libraries (${PROJECT_NAME}_Part1 LINK_PUBLIC FileHandler)

add_executable(${PROJECT_NAME}_Part2 part2.cpp)
target_link_libraries (${PROJECT_NAME}_Part2 LINK_PUBLIC FileHandler)