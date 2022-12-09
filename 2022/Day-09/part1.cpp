#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

std::vector<Point_t> tailPositions;

void AddTailPosition(const Point_t& rPos)
{
    bool contains = false;
    for(const Point_t& rListPos : tailPositions)
    {
        if(rListPos == rPos)
        {
            contains = true;
            break;
        }
    }
    if(!contains)
    {
        tailPositions.push_back(rPos);
    }
}

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);

    Point_t currentHead(0,0); // x, y
    Point_t currentTail(0,0); // x, y

    AddTailPosition(currentTail);

    if (file.IsOpen())
    {
        // Read the file
        std::vector<std::string> splitLine;
        while(file.GetLineSplit(splitLine," "))
        {
            uint steps = std::stoul(splitLine[1]);

            for(uint currentStep = 0; currentStep < steps; ++currentStep)
            {
                switch(splitLine[0][0])
                {
                case 'R':
                {
                    currentHead.first++;
                    if(currentHead.first > currentTail.first+1)
                    {
                        currentTail.first = currentHead.first-1;
                        currentTail.second = currentHead.second;
                        AddTailPosition(currentTail);
                    }
                    break;
                }
                case 'D':
                {
                    currentHead.second--;
                    if(currentHead.second < currentTail.second - 1)
                    {
                        currentTail.second = currentHead.second + 1;
                        currentTail.first = currentHead.first;
                        AddTailPosition(currentTail);
                    }
                    break;
                }
                case 'L':
                {
                    currentHead.first--;
                    if(currentHead.first < currentTail.first-1)
                    {
                        currentTail.first = currentHead.first+1;
                        currentTail.second = currentHead.second;
                        AddTailPosition(currentTail);
                    }
                    break;
                }
                case 'U':
                {
                    currentHead.second++;
                    if(currentHead.second > currentTail.second + 1)
                    {
                        currentTail.second = currentHead.second - 1;
                        currentTail.first = currentHead.first;
                        AddTailPosition(currentTail);
                    }
                    break;
                }
                }
            }
        }
    }
    std::cout<<"Total tail positions: "<<tailPositions.size()<<std::endl;
    return 0;
}