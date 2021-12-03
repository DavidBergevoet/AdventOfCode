#include <iostream>
#include <bitset>

#define BYTE_SIZE 12

#include "FileHandler.hpp"

enum class MostCommon
{
    ONES,
    ZEROS,
    EQUAL
};

MostCommon GetMostCommonFromBinaryList(const std::vector<std::bitset<BYTE_SIZE>>& rList, uint32_t index)
{
    uint32_t numberOfOnes = 0;
    for(size_t j = 0; j < rList.size(); ++j)
    {
        if(rList[j][index])
        {
            numberOfOnes++;
        }
    }
    if(numberOfOnes > (double)rList.size() / 2.0)
    {
        return MostCommon::ONES;
    }
    else if(numberOfOnes < (double)rList.size() / 2.0)
    {
        return MostCommon::ZEROS;
    }else
    {
        return MostCommon::EQUAL;
    }
}

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);
    
    uint32_t numberOfLines=0;
    std::vector<std::bitset<BYTE_SIZE>> binaryValues;

    if(file.IsOpen())
    {
        std::string line;
        while(file.GetLine(line))
        {
            numberOfLines++;
            std::bitset<BYTE_SIZE> value(line);
            binaryValues.push_back(value);
        }
        
        // Find the Oxygen Rating
        std::vector<std::bitset<BYTE_SIZE>> binaryValuesCopy = binaryValues;
        std::bitset<BYTE_SIZE> oxygenRating;
        for(int32_t i = BYTE_SIZE -1; i >=0;--i)
        {
            // Get most common character
            MostCommon mostCommon = GetMostCommonFromBinaryList(binaryValuesCopy, i);

            for(size_t j = 0; j < binaryValuesCopy.size(); ++j)
            {
                switch(mostCommon)
                {
                    case MostCommon::EQUAL:
                    case MostCommon::ONES:
                    {
                        if(!binaryValuesCopy[j][i])
                        {
                            binaryValuesCopy.erase(binaryValuesCopy.begin() + j);
                            j--;
                        }
                        break;
                    }
                    case MostCommon::ZEROS:
                    {
                        if(binaryValuesCopy[j][i])
                        {
                            binaryValuesCopy.erase(binaryValuesCopy.begin() + j);
                            j--;
                        }
                        break;
                    }
                }
            }
            if(binaryValuesCopy.size() == 1)
            {
                oxygenRating = binaryValuesCopy[0];
                break;
            }
        }
        
        // Find the C02 Rating
        binaryValuesCopy = binaryValues;
        std::bitset<BYTE_SIZE> co2Rating;
        for(int32_t i = BYTE_SIZE -1; i >=0;--i)
        {
            // Get most common character
            MostCommon mostCommon = GetMostCommonFromBinaryList(binaryValuesCopy, i);

            for(size_t j = 0; j < binaryValuesCopy.size(); ++j)
            {
                switch(mostCommon)
                {
                    case MostCommon::EQUAL:
                    case MostCommon::ONES:
                    {
                        if(binaryValuesCopy[j][i])
                        {
                            binaryValuesCopy.erase(binaryValuesCopy.begin() + j);
                            j--;
                        }
                        break;
                    }
                    case MostCommon::ZEROS:
                    {
                        if(!binaryValuesCopy[j][i])
                        {
                            binaryValuesCopy.erase(binaryValuesCopy.begin() + j);
                            j--;
                        }
                        break;
                    }
                }
            }
            if(binaryValuesCopy.size() == 1)
            {
                co2Rating = binaryValuesCopy[0];
                break;
            }
        }
        std::cout<<"OxygenRating:\t"<<oxygenRating<<"\t"<<oxygenRating.to_ullong()<<std::endl;
        std::cout<<"C02Rating:\t"<<co2Rating<<"\t"<<co2Rating.to_ullong()<<std::endl;
        std::cout<<"Multiplied:\t"<<oxygenRating.to_ullong() * co2Rating.to_ullong()<<std::endl;
    }

    return 0;
}