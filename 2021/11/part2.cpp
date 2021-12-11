#include <iostream>
#include "FileHandler.hpp"
#include "Octopus.hpp"
#include "Matrix.hpp"

typedef std::pair<uint32_t, uint32_t> Point;

Matrix<Octopus> octopusMap;

std::vector<Point> GetAdjacentPoints(const Point& rPoint)
{
    std::vector<Point> adjacent;
    if(rPoint.first == 0)
    {
        if(rPoint.second == 0)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 1)); //D
        }
        else if(rPoint.second == octopusMap.GetColumns()-1)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second - 1)); //D
        }
        else
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second - 1)); //D
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 1)); //D
        }
    }
    else if (rPoint.first == octopusMap.GetRows()-1)
    {
        if(rPoint.second == 0)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 1)); //D
        }
        else if(rPoint.second == octopusMap.GetColumns()-1)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second - 1)); //D
        }
        else
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 1)); //D
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second - 1)); //D
        }
    }else
    {
        if(rPoint.second == 0)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 1)); //D
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 1)); //D
        }
        else if(rPoint.second == octopusMap.GetColumns()-1)
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second - 1)); //D
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second - 1)); //D
        }
        else
        {
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second + 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 0));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 0, rPoint.second - 1));
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second - 1)); //D
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first + 1, rPoint.second + 1)); //D
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second - 1)); //D
            adjacent.push_back(std::make_pair<uint32_t, uint32_t>(rPoint.first - 1, rPoint.second + 1)); //D
        }
    }
    return adjacent;
}

void AddEnergyToOctopus(size_t row, size_t column)
{
    uint8_t energyLevelBefore = octopusMap[row][column].GetEnergyLevel();
    octopusMap[row][column].AddEnergyLevel();
    if(energyLevelBefore == 9)
    {
        std::vector<Point> adjacent =  GetAdjacentPoints(std::make_pair<uint32_t, uint32_t>(row, column));
        for(const Point& rPoint : adjacent)
        {
            AddEnergyToOctopus(rPoint.first, rPoint.second);
        }
    }
}

void ExecuteStep()
{
    for(size_t row = 0; row < octopusMap.GetRows(); ++row)
    {
        for(size_t column = 0; column < octopusMap.GetColumns(); ++column)
        {
            AddEnergyToOctopus(row, column);
        }
    }
    // std::cout<<octopusMap.ToString()<<std::endl;
    for(size_t row = 0; row < octopusMap.GetRows(); ++row)
    {
        for(size_t column = 0; column < octopusMap.GetColumns(); ++column)
        {
            octopusMap[row][column].ResetFlash();
        }
    }
}

bool CheckAllFlashed()
{
    for(size_t row = 0; row < octopusMap.GetRows(); ++row)
    {
        for(size_t column = 0; column < octopusMap.GetColumns(); ++column)
        {
            if(octopusMap[row][column].GetEnergyLevel() != 0)
            {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");

    std::string line;
    while(file.GetLine(line))
    {
        octopusMap.SetColumns(line.size());
        std::vector<Octopus> octopusRow;
        for(char character : line)
        {
            Octopus tempOcto(character - '0');
            octopusRow.push_back(tempOcto);
        }
        octopusMap.AddRow(octopusRow);
    }

    size_t steps = 0;
    while(!CheckAllFlashed())
    {
        steps++;
        // std::cout<<"Step: "<<steps<<std::endl;
        ExecuteStep();

    }
    std::cout<<octopusMap.ToString()<<std::endl;
    std::cout<<"Number of steps: "<<steps<<std::endl;
    std::cout<<"Total flashed: "<<Octopus::GetTotalFlashed()<<std::endl;
    return 0;
}
