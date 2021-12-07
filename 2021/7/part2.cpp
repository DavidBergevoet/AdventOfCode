#include <iostream>
#include "FileHandler.hpp"

std::vector<uint32_t> crabList;
std::vector<uint32_t> fuelMap;

void PrintCrabList()
{
    std::cout<<"CrabList: "<<crabList.size()<<std::endl;
    for(uint32_t crab : crabList)
    {
        std::cout<<crab<<" ";
    }
    std::cout<<std::endl;
}

void PrintFuelMap()
{
    std::cout<<"FuelMap: "<<fuelMap.size()<<std::endl;
    for(uint32_t fuel : fuelMap)
    {
        std::cout<<fuel<<" ";
    }
    std::cout<<std::endl;
}

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");
    if(!file.GetLineSplit(crabList, ","))
        throw std::invalid_argument("File cannot be opened");

    // PrintCrabList();

    // Get the max x value of the crabs
    uint16_t maxX = 0;
    for(uint32_t crab : crabList)
    {
        if(crab > maxX)
            maxX = crab;
    }
    fuelMap.resize(maxX + 1);

    // Get the amount of fuel for every crab
    for(uint16_t crab : crabList)
    {
        for(int32_t i = 0; i < fuelMap.size(); ++i)
        {
            uint32_t diff = abs(i - (int32_t)crab);
            uint32_t fuel = 0;
            for(size_t f = 1; f <= diff; ++f)
                fuel += f;
            fuelMap[i] += fuel;
        }
    }

    PrintFuelMap();

    // Get lowest amount of fuel
    uint32_t lowestFuel = fuelMap[0];
    size_t lowestFuelIndex = 0;

    for(size_t i = 0; i < fuelMap.size(); ++i)
    {
        if(fuelMap[i] < lowestFuel)
        {
            lowestFuel = fuelMap[i];
            lowestFuelIndex = i;
        }
    }

    std::cout<<"Lowest fuel index: "<<lowestFuelIndex<<"\tTotal fuel: "<<lowestFuel<<std::endl;
    
    return 0;
}
