#include <iostream>
#include <vector>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";
    std::vector<uint64_t> elfVector(1);

    FileHandler file(filePath);
    if(file.IsOpen())
    {
        // Read the file
        std::string line;
        while(file.GetLine(line))
        {
            if(line != "")
            {
                uint64_t calorie = std::stoul(line);
                elfVector.at(elfVector.size()-1) += calorie;
            }else
            {
                elfVector.push_back(0);
            }
        }
    }

    for(auto i : elfVector)
    {
        std::cout<<"Calorie "<<i<<std::endl;
    }
    return 0;
}