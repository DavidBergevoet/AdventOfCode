#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";
    std::vector<uint32_t> fileInputVector;

    std::ifstream file(filePath);
    if(file.is_open())
    {
        // Read the file
        std::string line;
        while(std::getline(file, line))
        {
            fileInputVector.push_back(std::stoul(line));
        }

        // Get the groups
        std::vector<uint32_t> groupVector;
        for(size_t i =0 ; i < fileInputVector.size()-2; ++i)
        {
            uint32_t sum = fileInputVector[i] + fileInputVector[i+1] + fileInputVector[i+2];
            groupVector.push_back(sum);
        }

        // Loop through groups
        uint32_t increases = 0;
        for(size_t i = 1; i < groupVector.size(); ++i)
        {
            if(groupVector[i-1] < groupVector[i])
            {
                increases++;
            }
        }
        std::cout<<"Total: "<<increases<<std::endl;
    }
    else
    {
        std::cerr<<"File cannot be opened"<<std::endl;
        return 1;
    }
    file.close();
    return 0;
}
