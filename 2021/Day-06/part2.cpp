#include <iostream>

#include "FileHandler.hpp"

#define SIMULATION_DAYS 256

std::vector<uint64_t> fishList;

uint64_t GetTotalFish()
{
    uint64_t returnValue = 0;
    for(uint64_t value : fishList)
    {
        returnValue += value;
    }
    return returnValue;
}

void PrintFishList()
{
    for(uint64_t value : fishList)
    {
        std::cout<<value<<" ";
    }
    std::cout<<std::endl;
}

void SimulateDay()
{
    uint64_t newFishies = 0;
    uint64_t parentFishies = 0;
    for(size_t i = 0; i < fishList.size(); ++i)
    {
        if(i == 0)
        {
            newFishies = parentFishies = fishList[i];
            fishList[i] = fishList[i+1];
        }
        else if(i == fishList.size() - 1)
        {
            fishList[i] = newFishies;
        }
        else if(i == 6)
        {
            fishList[i] = fishList[i+1] + parentFishies;
        }
        else
        {
            fishList[i] = fishList[i+1];
        }

    }
}

int main(int argc, char const *argv[])
{
    // Parse initial list
    std::vector<uint32_t> initialState;
    FileHandler file("input.txt");
    if(!file.GetLineSplit(initialState, ","))
        throw std::invalid_argument("Cannot open the file!");
    
    // Fill the fish list
    fishList.resize(9);
    for(uint32_t value : initialState)
    {
        if(value < 9)
        {
            fishList[value] += 1;
        }
    }

    PrintFishList();

    for(size_t i = 0; i<SIMULATION_DAYS;++i)
    {
        SimulateDay();
        // std::cout<<"After "<<i+1<<" Days\n\t";
        // PrintFishList();
    }
    PrintFishList();
    std::cout<<"Simulated days: "<<SIMULATION_DAYS<<std::endl;
    std::cout<<"Total fish: "<<GetTotalFish()<<std::endl;
    return 0;
}
