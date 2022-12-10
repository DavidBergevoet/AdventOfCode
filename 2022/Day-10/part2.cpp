#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);
    
    const uint CRT_HEIGHT=6;
    const uint CRT_WIDTH=40;

    uint currentRow = 0;

    Matrix<char> CRT(CRT_HEIGHT, CRT_WIDTH);

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

    for(uint i = 0; i < instructions.size(); ++i)
    {
        for(uint step = 0; step < instructions[i].first; ++step)
        {
            if(((currentStep) % CRT_WIDTH) == 0 && currentStep != 0)
            {
                currentRow++;
            }

            if(currentRow < CRT_HEIGHT)
            {
                if((currentStep % 40) >= x-1 && (currentStep % 40) <= x+1)
                {
                    CRT.At(currentRow,currentStep%CRT_WIDTH) = '#';
                }
                else
                {
                    CRT.At(currentRow,currentStep%CRT_WIDTH)  = '.';
                }
            }
            currentStep++;
        }
        x += instructions[i].second;
    }


    std::cout<<CRT<<std::endl;
    return 0;
}