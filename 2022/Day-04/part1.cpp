#include <iostream>
#include <vector>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    uint64_t totalOverlap = 0;

    FileHandler file(filePath);
    if (file.IsOpen())
    {
        // Read the file
        std::vector<std::string> line;
        while (file.GetLineSplit(line, ","))
        {
            uint firstStartSection = std::stoul(file.SplitString(line[0],"-")[0]);
            uint firstEndSection = std::stoul(file.SplitString(line[0],"-")[1]);
            uint secondStartSection = std::stoul(file.SplitString(line[1],"-")[0]);
            uint secondEndSection = std::stoul(file.SplitString(line[1],"-")[1]);

            if(secondStartSection >= firstStartSection && secondEndSection <= firstEndSection)
            {
                totalOverlap++;
            }
            else if (firstStartSection >= secondStartSection && firstEndSection <= secondEndSection)
            {
                totalOverlap++;
            }
        }
    }
    std::cout<<"Overlapping sections: "<<totalOverlap<<std::endl;
    return 0;
}