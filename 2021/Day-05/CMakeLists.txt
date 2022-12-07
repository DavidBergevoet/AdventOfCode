cmake_minimum_required(VERSION 3.10)
cmake_minimum_required(VERSION 3.10)

get_filename_component(day ${CMAKE_CURRENT_BINARY_DIR} NAME)
get_filename_component(year_path ${CMAKE_CURRENT_BINARY_DIR} DIRECTORY)
get_filename_component(year ${year_path} NAME)

project(AdventOfCode-${year}-${day}) 

configure_file("input.txt" "input.txt" COPYONLY)

add_executable(${PROJECT_NAME}_Part1 
    part1.cpp
    Map.cpp
)
add_executable(${PROJECT_NAME}_Part2 
    part2.cpp
    Map.cpp
)

target_link_libraries (${PROJECT_NAME}_Part1 LINK_PUBLIC FileHandler)
target_link_libraries (${PROJECT_NAME}_Part1 LINK_PUBLIC Matrix)
target_link_libraries (${PROJECT_NAME}_Part2 LINK_PUBLIC FileHandler)
target_link_libraries (${PROJECT_NAME}_Part2 LINK_PUBLIC Matrix)