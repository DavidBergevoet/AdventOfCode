#include <iostream>
#include <algorithm>
#include "Matrix.hpp"
#include "FileHandler.hpp"

typedef std::pair<uint32_t, uint32_t> Point;

Matrix<uint32_t> smokeMap;

std::vector<Point> GetAdjacentPoints(const Point& rPoint)
{
    std::vector<Point> adjacent;
    if(rPoint.first == 0)
    {
        if(rPoint.second == 0)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
        }
        else if(rPoint.second == smokeMap.GetColumns()-1)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
        }
        else
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
        }
    }
    else if (rPoint.first == smokeMap.GetRows()-1)
    {
        if(rPoint.second == 0)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
        }
        else if(rPoint.second == smokeMap.GetColumns()-1)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
        }
        else
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
        }
    }else
    {
        if(rPoint.second == 0)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
        }
        else if(rPoint.second == smokeMap.GetColumns()-1)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
        }
        else
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
        }
    }
    return adjacent;
}

uint32_t GetBasinSizeInternal(const Point& rPoint, std::vector<Point>& rDiscovered)
{
    // Check if discovered
    for(const Point& point : rDiscovered)
    {
        if(point == rPoint)
            return 0;
    }

    rDiscovered.push_back(rPoint);
    // If the smoke map contains a 9 return
    if(smokeMap[rPoint.first][rPoint.second] == 9)
        return 0;
    
    // Add this node to the sum and add all adjacent sums to it.
    uint32_t sum = 1;
    for(const Point& point : GetAdjacentPoints(rPoint))
    {
        sum += GetBasinSizeInternal(point, rDiscovered);
    }
    return sum;
}

uint32_t GetBasinSize(const Point& beginPoint)
{
    std::vector<Point> discoveredPoints;
    uint32_t size = 0;
    size = GetBasinSizeInternal(beginPoint, discoveredPoints);
    return size;
}

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");
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

    std::vector<Point> lowestPoints;
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
                    lowestPoints.push_back(std::make_pair<uint32_t,uint32_t>(row,column));
                }
                else if(column == smokeMap.GetColumns()-1
                    && smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row+1][column]
                )
                {
                    lowestPoints.push_back(std::make_pair<uint32_t,uint32_t>(row,column));
                }
                else if(smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row][column+1]
                    && smokeMap[row][column] < smokeMap[row+1][column]
                )
                {
                    lowestPoints.push_back(std::make_pair<uint32_t,uint32_t>(row,column));
                }
            }
            else if(row == smokeMap.GetRows()-1)
            {
                if(column == 0 
                    && smokeMap[row][column] < smokeMap[row][column+1]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                )
                {
                    lowestPoints.push_back(std::make_pair<uint32_t,uint32_t>(row,column));
                }
                else if(column == smokeMap.GetColumns()-1
                    && smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                )
                {
                    lowestPoints.push_back(std::make_pair<uint32_t,uint32_t>(row,column));
                }
                else if(smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row][column+1]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                )
                {
                    lowestPoints.push_back(std::make_pair<uint32_t,uint32_t>(row,column));
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
                    lowestPoints.push_back(std::make_pair<uint32_t,uint32_t>(row,column));
                }
                else if(column == smokeMap.GetColumns()-1
                    && smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row+1][column]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                )
                {
                    lowestPoints.push_back(std::make_pair<uint32_t,uint32_t>(row,column));
                }
                else if(smokeMap[row][column] < smokeMap[row][column-1]
                    && smokeMap[row][column] < smokeMap[row][column+1]
                    && smokeMap[row][column] < smokeMap[row-1][column]
                    && smokeMap[row][column] < smokeMap[row+1][column]
                )
                {
                    lowestPoints.push_back(std::make_pair<uint32_t,uint32_t>(row,column));
                }
            }
        }
    }
    std::vector<uint32_t> basinSizes;
    basinSizes.resize(3);
    for(const std::pair<uint32_t, uint32_t>& point : lowestPoints)
    {
        uint32_t basinSize = GetBasinSize(point);
        bool isGreater = false;
        for(size_t i = 0; i < basinSizes.size();++i)
        {
            if(basinSize > basinSizes[i])
            {
                basinSizes.erase(basinSizes.begin()+i);
                isGreater = true;
                break;
            }
        }
        if(isGreater)
        {
            basinSizes.push_back(basinSize);
            std::sort(basinSizes.begin(),basinSizes.end());
        }
    }

    uint32_t multipliedBasinSize = basinSizes[0] * basinSizes[1] * basinSizes[2];
    std::cout<<"Multiplied BasinSize: "<<multipliedBasinSize<<std::endl;

    return 0;
}
