#include <iostream>
#include <vector>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    uint64_t highestElf = 0;
    uint64_t currentCalorie = 0;
    uint64_t highestElfIndex = 1;
    uint64_t currentIndex = 1;

    FileHandler file(filePath);
    if(file.IsOpen())
    {
        // Read the file
        std::string line;
        while(file.GetLine(line))
        {
            if(line != "")
            {
                currentCalorie += std::stoul(line);
            }else
            {
                if(currentCalorie > highestElf)
                {
                    highestElf = currentCalorie;
                    highestElfIndex = currentIndex;
                }
                currentCalorie = 0;
                currentIndex++;
            }
        }
    }

    std::cout<<"Highest elf: "<<highestElfIndex<<" Calories: "<<highestElf<<std::endl;
    return 0;
}