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
    std::vector<Point_t> currentTail(9); // x, y

    AddTailPosition(currentTail[0]);

    if (file.IsOpen())
    {
        // Read the file
        std::vector<std::string> splitLine;
        while(file.GetLineSplit(splitLine," "))
        {
            uint steps = std::stoul(splitLine[1]);

            for(uint currentStep = 0; currentStep < steps; ++currentStep)
            {
                Point_t previousLocation = currentHead;
                switch(splitLine[0][0])
                {
                case 'R':
                {
                    currentHead.first++;
                    break;
                }
                case 'D':
                {
                    currentHead.second--;
                    break;
                }
                case 'L':
                {
                    currentHead.first--;
                    break;
                }
                case 'U':
                {
                    currentHead.second++;
                    break;
                }
                }
                for(size_t i = 0;i< currentTail.size();++i)
                    {
                        Point_t comparisonPoint;
                        if(i == 0)
                        {
                            comparisonPoint = currentHead;
                        }else{
                            comparisonPoint = currentTail[i-1];
                        }

                        // T bottom left of CP
                        if(currentTail[i].first < comparisonPoint.first -1 && currentTail[i].second < comparisonPoint.second - 1)
                        {
                            currentTail[i].first += 1;
                            currentTail[i].second += 1;
                        }

                        // T bottom right of CP
                        else if(currentTail[i].first > comparisonPoint.first + 1 && currentTail[i].second < comparisonPoint.second - 1)
                        {
                            currentTail[i].first -= 1;
                            currentTail[i].second += 1;
                        }

                        // T top right of CP
                        else if(currentTail[i].first > comparisonPoint.first + 1 && currentTail[i].second > comparisonPoint.second + 1)
                        {
                            currentTail[i].first -= 1;
                            currentTail[i].second -= 1;
                        }

                        // T top left of CP
                        else if(currentTail[i].first < comparisonPoint.first - 1 && currentTail[i].second > comparisonPoint.second + 1)
                        {
                            currentTail[i].first += 1;
                            currentTail[i].second -= 1;
                        }
                        
                        // T left of CP
                        else if(currentTail[i].first < comparisonPoint.first - 1)
                        {
                            currentTail[i].first = comparisonPoint.first -1;
                            currentTail[i].second = comparisonPoint.second;
                        }

                        // T bottom of CP
                        else if(currentTail[i].second < comparisonPoint.second - 1)
                        {
                            currentTail[i].first = comparisonPoint.first;
                            currentTail[i].second = comparisonPoint.second - 1;
                        }

                        // T right of CP
                        else if(currentTail[i].first > comparisonPoint.first + 1)
                        {
                            currentTail[i].first = comparisonPoint.first + 1;
                            currentTail[i].second = comparisonPoint.second;
                        }

                        // T top of CP
                        else if(currentTail[i].second > comparisonPoint.second + 1)
                        {
                            currentTail[i].first = comparisonPoint.first;
                            currentTail[i].second = comparisonPoint.second + 1;
                        }
                    }
                AddTailPosition(currentTail[8]);
            }
        }
    }
    
    std::cout<<"Total tail positions: "<<tailPositions.size()<<std::endl;
    return 0;
}