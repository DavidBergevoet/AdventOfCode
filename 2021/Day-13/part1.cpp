#include <iostream>
#include "Matrix.hpp"
#include "FileHandler.hpp"

Matrix<bool> page;

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");

    // Generate the bitmap
    std::vector<std::pair<uint32_t, uint32_t>> points;
    uint32_t maxX = 0, maxY = 0;
    std::vector<uint32_t> line;
    while(file.GetLineSplit(line, ","))
    {
        if(line.size() == 0)
            break;
        
        if(line[0] > maxX)
            maxX = line[0];
        if(line[1] > maxY)
            maxY = line[1];

        points.push_back(std::pair<uint32_t, uint32_t>(line[0], line[1]));
    }

    page.Resize(maxY + 1, maxX + 1);
    for(const auto& rPoint : points)
    {
        page[rPoint.second][rPoint.first] = true;
    }
    // std::cout<< page << std::endl;

    // Extract fold instructions
    std::vector<std::pair<bool, uint32_t>> instructions;
    std::vector<std::string> stringListLine;
    while(file.GetLineSplit(stringListLine, " "))
    {
        std::vector<std::string> instructionList = FileHandler::SplitString(stringListLine[2],"=");
        bool isX = (instructionList[0] == "x");
        instructions.push_back(std::pair<bool, uint32_t>(isX, std::stoul(instructionList[1])));
    }

    // Execute instructions
    Matrix<bool> previousOutput = page;
    Matrix<bool> output = page;
    for(size_t i = 0; i < instructions.size(); ++i)
    {
        previousOutput = output;
        if(instructions[i].first)
        {
            output.Resize(previousOutput.GetRows(), previousOutput.GetColumns()/2);
            for(size_t row = 0; row < output.GetRows(); ++row)
            {
                for(size_t col = 0; col < instructions[i].second; ++col)
                {
                    output[row][col] = 
                        previousOutput[row][col] | previousOutput[row][previousOutput.GetColumns() - col - 1];
                }
            }
        }
        else
        {
            output.Resize(previousOutput.GetRows()/2, previousOutput.GetColumns());
            for(size_t row = 0; row < instructions[i].second; ++row)
            {
                for(size_t col = 0; col < output.GetColumns(); ++col)
                {
                    output[row][col] = 
                        previousOutput[row][col] | previousOutput[previousOutput.GetRows() - row - 1][col];
                }
            }
        }
    }

     std::cout<<"Output\n"<<output<<std::endl;

    uint32_t numberOfDots = 0;

    for(size_t row = 0; row < output.GetRows(); ++row)
    {
        for(size_t col = 0; col < output.GetColumns(); ++col)
        {
            if(output[row][col])
                numberOfDots++;
        }
    }

    std::cout<<"Number of dots: "<<numberOfDots<<std::endl;

    return 0;
}
