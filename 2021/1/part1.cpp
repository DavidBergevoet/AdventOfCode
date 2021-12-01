#include <iostream>
#include <vector>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";
    std::vector<uint32_t> fileInputVector;

    FileHandler file(filePath);
    if(file.IsOpen())
    {
        // Read the file
        std::string line;
        while(file.GetLine(line))
        {
            fileInputVector.push_back(std::stoul(line));
        }

        // Get the number of increases
        uint32_t increasedNumbers = 0;
        for(size_t i = 1; i<fileInputVector.size(); ++i)
        {
            if(fileInputVector[i-1] < fileInputVector[i])
            {
                increasedNumbers++;
            }
        }
        std::cout<<"Total: "<<increasedNumbers<<std::endl;
    }
    else
    {
        std::cerr<<"File cannot be opened"<<std::endl;
        return 1;
    }
    file.Close();
    return 0;
}
