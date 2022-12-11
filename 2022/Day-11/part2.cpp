#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

struct Monkey{
    std::vector<uint64_t> m_items;
    char m_operator; // + - * /
    std::string m_operationRightHandSide;
    uint64_t m_divisible;
    uint64_t m_trueMonkeyNumber;
    uint64_t m_falseMonkeyNumber;

    uint64_t m_inspections = 0;
};

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);

    std::vector<Monkey> monkeyList;

    uint division = 1;

    if (file.IsOpen())
    {
        // Read the file
        std::string line;

        // Initialize monkey list
        Monkey tempMonkey;
        while(file.GetLine(line))
        {
            if(line.size() == 0)
            {
                monkeyList.push_back(tempMonkey);
                division *= tempMonkey.m_divisible;
                tempMonkey = Monkey();
            }
            else
            {
                std::vector<std::string> splitLine = file.SplitString(line, " ");
                
                if(splitLine.size() > 3 && splitLine[2] == "Starting")
                {
                    for(size_t i  = 4; i < splitLine.size(); ++i)
                    {
                        tempMonkey.m_items.push_back(std::stoul(splitLine[i]));
                    }
                }
                else if(splitLine.size() > 3 && splitLine[2] == "Operation:")
                {
                    tempMonkey.m_operator = splitLine[6][0];
                    tempMonkey.m_operationRightHandSide = splitLine[7];
                }
                else if(splitLine.size() > 3 && splitLine[2] == "Test:")
                {
                    tempMonkey.m_divisible = std::stoul(splitLine[5]);
                }
                else if(splitLine.size() > 4 && splitLine[4] == "If")
                {
                    if(splitLine[5] == "true:")
                    {
                        tempMonkey.m_trueMonkeyNumber = std::stoul(splitLine[9]);
                    }
                    else
                    {
                        tempMonkey.m_falseMonkeyNumber = std::stoul(splitLine[9]);
                    }
                }
            }
        }
        division *= tempMonkey.m_divisible;
        monkeyList.push_back(tempMonkey);
    }

    // Start rounds
    for(size_t round = 0; round < 10000; ++round)
    {
        for(size_t i = 0; i < monkeyList.size(); ++i)
        {
            // Loop through the items
            while(monkeyList[i].m_items.size() != 0)
            {
                monkeyList[i].m_inspections++;
                // Determine new worryLevel
                uint value = 0;
                if(monkeyList[i].m_operationRightHandSide == "old")
                {
                    value = monkeyList[i].m_items[0];
                }
                else
                {
                    value = std::stoul(monkeyList[i].m_operationRightHandSide);
                }
                switch(monkeyList[i].m_operator)
                {
                    case '+':
                    {
                        monkeyList[i].m_items[0] += value;
                        break;
                    }
                    case '*':
                    {
                        monkeyList[i].m_items[0] *= value;
                        break;
                    }
                }

                // No more relief for you
                // monkeyList[i].m_items[0] /= 3;
                
                // Throw the item
                if(monkeyList[i].m_items[0] % monkeyList[i].m_divisible == 0)
                {
                    monkeyList[monkeyList[i].m_trueMonkeyNumber].m_items.push_back(monkeyList[i].m_items[0] % division);
                }
                else
                {
                    monkeyList[monkeyList[i].m_falseMonkeyNumber].m_items.push_back(monkeyList[i].m_items[0] % division);
                }
                monkeyList[i].m_items.erase(monkeyList[i].m_items.begin());
            }
        }
    }

    for(size_t i = 0; i < monkeyList.size(); ++i)
    {
        std::cout<<i<<" "<<monkeyList[i].m_items.size()<<" "<<monkeyList[i].m_operator<<" "<<monkeyList[i].m_operationRightHandSide<<" "<<monkeyList[i].m_divisible 
            << "-" <<monkeyList[i].m_trueMonkeyNumber << " "<<monkeyList[i].m_falseMonkeyNumber<<" : "<<monkeyList[i].m_inspections<<std::endl;
        for(uint item: monkeyList[i].m_items)
        {
            // std::cout<<"\tItem: "<<item<<std::endl;
        }
    }

    // Get the 2 highest monkeys
    uint64_t highestMonkeys[2] = {0, 0};
    for(const Monkey& rMonkey : monkeyList)
    {
        uint64_t currentLowest = (highestMonkeys[0] < highestMonkeys[1]) ? highestMonkeys[0] : highestMonkeys[1];
        uint64_t lowestIndex = (highestMonkeys[0] < highestMonkeys[1]) ? 0 : 1;

        if(rMonkey.m_inspections > currentLowest)
        {
            highestMonkeys[lowestIndex] = rMonkey.m_inspections;
        }
    }

    std::cout<<"Heighest values: "<<highestMonkeys[0]<< " - " << highestMonkeys[1]<<" Combined: "<<highestMonkeys[0] * highestMonkeys[1]<<std::endl;
    return 0;
}