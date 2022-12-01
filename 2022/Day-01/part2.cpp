#include <iostream>
#include <vector>
#include <algorithm>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";
    std::vector<uint64_t> elves;

    uint64_t currentCalorie = 0;

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
                elves.push_back(currentCalorie);
                currentCalorie = 0;
            }
        }
        elves.push_back(currentCalorie);
    }
    std::sort(elves.begin(),elves.end());
    uint64_t totalTopThree = 0;
    for(size_t i = 0;i<3;++i){
        std::cout<<elves[elves.size()-i-1]<<std::endl;
        totalTopThree += elves[elves.size()-i-1];
    }
    std::cout<<"---------------\n"<<totalTopThree<<std::endl;

    return 0;
}