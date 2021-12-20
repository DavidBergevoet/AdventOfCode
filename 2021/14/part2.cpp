#include <iostream>
#include <algorithm>
#include <map>
#include <unordered_map>
#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");
    std::string beginSequence;
    file.GetLine(beginSequence);
    std::cout << "BeginSequence: " << beginSequence << std::endl;
    char last = beginSequence[beginSequence.size()-1];

    std::map<std::string,char> insertionMap;
    std::unordered_map<std::string, uint64_t> pairMap;

    for(size_t i = 0; i < beginSequence.size()-1; ++i)
    {
        std::string pair;
        pair += beginSequence[i];
        pair += beginSequence[i+1];
        if(pairMap.find(pair) != pairMap.end())
        {
            pairMap[pair] += 1;
        }
        else
        {
            pairMap[pair] = 1;
        }
    }

    // std::cout<<"PairMap:"<<std::endl;
    // for(std::unordered_map<std::string, uint64_t>::iterator it = pairMap.begin(); it != pairMap.end(); ++it)
    // {
    //     std::cout<<"\tKey: "<<it->first<<"\tVal: "<<it->second<<std::endl;
    // }

    std::vector<std::string> splitLine;
    while(file.GetLineSplit(splitLine, " -> "))
    {
        if(splitLine.size() != 0)
            insertionMap[splitLine[0]] = splitLine[1][0];
    }

    // std::cout<<"InsertionMap:"<<std::endl;
    // for(std::map<std::string, char>::iterator it = insertionMap.begin(); it != insertionMap.end(); ++it)
    // {
    //     std::cout<<"\tKey: "<<it->first<<"\tVal: "<<it->second<<std::endl;
    // }

    std::unordered_map<std::string, uint64_t> tempPairMap, newPairMap = pairMap;
    for(size_t step = 0; step < 40; ++step)
    {
        // std::cout<<"Step:"<<step<<std::endl;
        tempPairMap = newPairMap;
        newPairMap.clear();
        std::string firstPair, secondPair;
        for(auto it = tempPairMap.begin(); it != tempPairMap.end(); ++it)
        {
            firstPair = secondPair = "";
            char middleChar = insertionMap[it->first];
            firstPair = it->first[0];
            firstPair += middleChar;
            secondPair += middleChar;
            secondPair += it->first[1];
            // std::cout<<"F: "<<firstPair<<" S: "<<secondPair<<std::endl;

            if(newPairMap.find(firstPair) != newPairMap.end())
                newPairMap[firstPair] += it->second;
            else
                newPairMap[firstPair] = it->second;

            if(newPairMap.find(secondPair) != newPairMap.end())
                newPairMap[secondPair] +=  it->second;
            else
                newPairMap[secondPair] = it->second;

        }
    }
    
    // std::cout<<"NewPairMap:"<<std::endl;
    // for(std::unordered_map<std::string, uint64_t>::iterator it = newPairMap.begin(); it != newPairMap.end(); ++it)
    // {
    //     std::cout<<"\tKey: "<<it->first<<"\tVal: "<<it->second<<std::endl;
    // }

    uint64_t mostCommon = 0, 
        leastCommon = UINT64_MAX;

    std::unordered_map<char, uint64_t> charCount;
    for(std::unordered_map<std::string, uint64_t>::iterator it = newPairMap.begin(); it != newPairMap.end(); ++it)
    {
        if(charCount.find(it->first[0]) != charCount.end())
            charCount[it->first[0]] += it->second;
        else
            charCount[it->first[0]] = it->second;
    }
    charCount[last] += 1;
    
    for(std::unordered_map<char, uint64_t>::iterator it = charCount.begin(); it != charCount.end(); ++it)
    {
        // std::cout<<it->first<<"\t"<<it->second<<std::endl;
        if(it->second > mostCommon)
            mostCommon = it->second;
        if(it->second < leastCommon)
            leastCommon = it->second;
    }
    std::cout<<"Most common: "<<mostCommon<<std::endl;
    std::cout<<"Least common: "<<leastCommon<<std::endl;
    std::cout<<mostCommon-leastCommon<<std::endl;
    
    return 0;
}
