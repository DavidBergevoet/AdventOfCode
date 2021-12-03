#include <iostream>
#include <bitset>

#define BYTE_SIZE 5

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);
    
    uint32_t numberOfLines=0;
    std::vector<uint32_t> numberOfOnes;
    std::vector<std::bitset<BYTE_SIZE>> binaryValues;

    numberOfOnes.resize(BYTE_SIZE);

    if(file.IsOpen())
    {
        std::string line;
        while(file.GetLine(line))
        {
            numberOfLines++;
            std::bitset<BYTE_SIZE> value(line);
            binaryValues.push_back(value);

            for(size_t i =0;i<line.size();++i)
            {
                if(line[i] == '1')
                {
                    numberOfOnes[i] = numberOfOnes[i]+1;
                }
            }
        }
        std::cout<<"number of lines: "<<numberOfLines<<std::endl;
        //Convert numberOfOnes to bitset
        std::bitset<BYTE_SIZE> numberOfOnesBitSet, numberOfZerosBitset;
        for(size_t i = 0; i < numberOfOnes.size(); ++i)
        {
            std::cout<<"numberof 1:"<<numberOfOnes[i]<<std::endl;
            if(numberOfOnes[i] >= numberOfLines / 2){
                std::bitset<BYTE_SIZE> mask("10000");
                mask = mask >> i;
                numberOfOnesBitSet |= mask;
            }
        }
        numberOfZerosBitset = numberOfOnesBitSet;
        numberOfZerosBitset.flip();

        std::cout<<"NumberOfOnesBitset: "<<numberOfOnesBitSet<<std::endl;

        // ------------------ GET OXYGEN RATING -------------------------- //
        std::bitset<BYTE_SIZE> numberOfOnesBitSetCopy = numberOfOnesBitSet;
        std::bitset<BYTE_SIZE> oxygenRating;
        std::vector<std::bitset<BYTE_SIZE>> binaryValuesCopy = binaryValues;
        for(int32_t i = BYTE_SIZE-1;i >= 0; --i)
        {
            std::cout<<"Checking: "<<i<<std::endl;
            for(int32_t j=0; j<binaryValuesCopy.size(); ++j)
            {
                if(binaryValuesCopy[j][i] != numberOfOnesBitSetCopy[i])
                {
                    binaryValuesCopy.erase(binaryValuesCopy.begin()+ j);
                    j--;
                }else{
                    std::cout<<"\tContinuing: "<<binaryValuesCopy[j]<<std::endl;
                }
            }

            // Calc number of ones bitset
            numberOfOnesBitSetCopy.reset();
            for(int32_t i=BYTE_SIZE-1;i>=0; --i)
            {
                uint32_t temp=0;
                for(int32_t j=0; j<binaryValuesCopy.size(); ++j)
                {
                    if(binaryValues[j][i])
                    {
                        temp++;
                    }
                }
                std::cout<<temp<<std::endl;
                if(temp > binaryValuesCopy.size()/2)
                {
                    std::bitset<BYTE_SIZE> mask("10000");
                    numberOfOnesBitSetCopy |= (mask >> i);
                }
                else if(temp < binaryValuesCopy.size()/2)
                {

                }else // Equal
                {
                }
            }
            std::cout<<"New # 1 bitset"<<numberOfOnesBitSetCopy<<std::endl;

            std::cout<<std::endl;
            if(binaryValuesCopy.size() == 1)
            {
                std::cout<<binaryValuesCopy[0]<<std::endl;
                oxygenRating = binaryValuesCopy[0];
                break;
            }
        }

        std::cout<<"numberOfZeros:"<<numberOfZerosBitset<<std::endl;
        std::bitset<BYTE_SIZE> co2Rating;
        binaryValuesCopy = binaryValues;
        for(int32_t i = BYTE_SIZE-1;i >= 0; --i)
        {
            std::cout<<"Checking: "<<i<<std::endl;
            for(int32_t j=0; j<binaryValuesCopy.size(); ++j)
            {
                if(binaryValuesCopy[j][i] != numberOfZerosBitset[i])
                {
                    std::cout<<"Erasing: "<<binaryValuesCopy[j]<<std::endl;
                    binaryValuesCopy.erase(binaryValuesCopy.begin()+ j);
                    j--;
                }
            }

            std::cout<<std::endl;
            if(binaryValuesCopy.size() == 1)
            {
                std::cout<<binaryValuesCopy[0]<<std::endl;
                co2Rating = binaryValuesCopy[0];
                break;
            }
        }
        std::cout<<"C02 Rating: "<<co2Rating<<"\t"<<co2Rating.to_ullong()<<std::endl;
        std::cout<<"OxygenRating: "<<oxygenRating<<"\t"<<oxygenRating.to_ullong()<<std::endl;
        std::cout<<"Multiplied: "<<oxygenRating.to_ullong() * co2Rating.to_ullong()<<std::endl;

    }

    return 0;
}