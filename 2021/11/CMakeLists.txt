cmake_minimum_required(VERSION 3.10)

project(AdventOfCode-2021-11)

configure_file("input.txt" "input.txt" COPYONLY)

add_executable(${PROJECT_NAME}_Part1 
    part1.cpp
    Octopus.cpp
)

add_executable(${PROJECT_NAME}_Part2
    part2.cpp
    Octopus.cpp
)

target_link_libraries (${PROJECT_NAME}_Part1 LINK_PUBLIC FileHandler)
target_link_libraries (${PROJECT_NAME}_Part1 LINK_PUBLIC Matrix)

target_link_libraries (${PROJECT_NAME}_Part2 LINK_PUBLIC FileHandler)
target_link_libraries (${PROJECT_NAME}_Part2 LINK_PUBLIC Matrix)