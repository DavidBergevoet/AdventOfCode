#include <iostream>
#include <algorithm>
#include <map>
#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");
    std::string beginSequence;
    file.GetLine(beginSequence);
    std::cout << "BeginSequence: " << beginSequence << std::endl;

    std::vector<std::pair<std::string, char>> insertionRules;
    std::map<std::string,char> insertionMap;
    std::vector<std::string> splitLine;
    while(file.GetLineSplit(splitLine, " -> "))
    {
        if(splitLine.size() != 0)
        {
            insertionRules.push_back(std::pair<std::string, char>(splitLine[0],splitLine[1][0]));
            insertionMap[splitLine[0]] = splitLine[1][0];
        }
    }

    std::string previousSequence = beginSequence;
    std::string newSequence;
    for(size_t i = 0; i < 40; ++i)
    {
        std::cout<<"Step: "<<i<<std::endl;
        newSequence = "";
        newSequence += previousSequence[0];
        for(size_t i = 0; i < previousSequence.size() - 1; ++i)
        {
            std::string checkString;
            (checkString += previousSequence[i]) += previousSequence[i + 1];
            // std::cout << "CheckS: "<<checkString<<std::endl; 

            newSequence += insertionMap[checkString]; 

            // for(const auto& rRule : insertionRules)
            // {
            //     if(rRule.first == checkString)
            //     {
            //         newSequence += rRule.second;
            //         break;
            //     }
            // }
            newSequence += checkString[1];
        }
        previousSequence = newSequence;
    }
    // std::cout<<"Final sequence: "<<newSequence<<std::endl;

    std::vector<char> uniqueCharacters;
    for(char character : newSequence)
    {
        bool isIn = false;
        for(char unique : uniqueCharacters)
        {
            if(character == unique)
            {
                isIn = true;
                break;
            }
        }
        if(!isIn)
            uniqueCharacters.push_back(character);
    }


    uint64_t mostCommon = 0, leastCommon = UINT64_MAX;

    for(char unique : uniqueCharacters)
    {
        uint32_t count = std::count(newSequence.begin(), newSequence.end(), unique);
        if(count > mostCommon)
            mostCommon = count;
        if(count < leastCommon)
            leastCommon = count;
    }

    std::cout<<"Most common: "<<mostCommon<<std::endl;
    std::cout<<"Least common: "<<leastCommon<<std::endl;
    std::cout<<mostCommon-leastCommon<<std::endl;
    
    return 0;
}
