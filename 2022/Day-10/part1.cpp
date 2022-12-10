#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);

    // Number of cycles, number to add after cycle
    std::vector<std::pair<uint, int>> instructions;

    if (file.IsOpen())
    {
        // Read the file
        std::vector<std::string> lineSplit;
        while(file.GetLineSplit(lineSplit))
        {
            if(lineSplit.size() == 1) // Noop
            {
                instructions.push_back(std::make_pair<uint, int>(1, 0));
            }
            else // AddX
            {
                instructions.push_back(std::make_pair<uint, int>(2, std::stoi(lineSplit[1])));
            }
        }
    }

    int64_t x = 1;
    uint currentStep = 0;
    int64_t strength = 0;

    for(uint i = 0; i < instructions.size(); ++i)
    {
        for(uint step = 0; step < instructions[i].first; ++step)
        {
            currentStep ++;
            if(((currentStep + 20) % 40) == 0)
            {
                strength += (x * currentStep);
            }
        }
        x += instructions[i].second;
    }


    std::cout<<"X: "<<x<<" Steps: " << currentStep<<std::endl;
    
    std::cout<<"Signal strength: "<< strength<<std::endl;

    return 0;
}