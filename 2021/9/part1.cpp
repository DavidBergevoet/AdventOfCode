#include <iostream>
#include "Matrix.hpp"
#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");
    Matrix<uint32_t> smokeMap;
    std::string line;
    while(file.GetLine(line))
    {
        smokeMap.SetColumns(line.size());
        std::vector<uint32_t> lineNumbers;
        for(size_t i = 0; i < line.size(); ++i)
        {
            lineNumbers.push_back(line[i] - '0');
        }
        smokeMap.AddRow(lineNumbers);
    }
    uint32_t riskLevel;
    for(size_t row = 0; row < smokeMap.GetRows(); ++row)
    {
        for(size_t column = 0; column < smokeMap.GetColumns(); ++column)
        {
            if(row == 0)
            {
                if(column == 0 
                    && smokeMap[row][column] < smokeMap[row][column+1]
                    && smokeMap[row][column] < smokeMap[row+1][column]
                )
                {
                    riskLevel += smokeMap[row][column]+1;
                }
                else if(column == smokeMap.GetColumns()-1
                    && smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row+1][column]
                )
                {
                    riskLevel += smokeMap[row][column]+1;
                }
                else if(smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row][column+1]
                    && smokeMap[row][column] < smokeMap[row+1][column]
                )
                {
                    riskLevel += smokeMap[row][column]+1;
                }
            }
            else if(row == smokeMap.GetRows()-1)
            {
                if(column == 0 
                    && smokeMap[row][column] < smokeMap[row][column+1]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                )
                {
                    riskLevel += smokeMap[row][column]+1;
                }
                else if(column == smokeMap.GetColumns()-1
                    && smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                )
                {
                    riskLevel += smokeMap[row][column]+1;
                }
                else if(smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row][column+1]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                )
                {
                    riskLevel += smokeMap[row][column]+1;
                }
            }
            else
            {
                if(column == 0
                    && smokeMap[row][column] < smokeMap[row][column+1]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                    && smokeMap[row][column] < smokeMap[row+1][column]
                )
                {
                    riskLevel += smokeMap[row][column]+1;
                }
                else if(column == smokeMap.GetColumns()-1
                    && smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row+1][column]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                )
                {
                    riskLevel += smokeMap[row][column]+1;
                }
                else if(smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row][column+1]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                    && smokeMap[row][column] < smokeMap[row+1][column]
                )
                {
                    riskLevel += smokeMap[row][column] +1;
                }
            }
        }
    }
    std::cout<<"Risk level: "<<riskLevel<<std::endl;
    return 0;
}
