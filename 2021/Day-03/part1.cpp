#include <iostream>
#include <bitset>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);
    
    uint32_t numberOfLines=0;
    std::vector<uint32_t> numberOfOnes;

    numberOfOnes.resize(12);

    if(file.IsOpen())
    {
        std::string line;
        while(file.GetLine(line))
        {
            numberOfLines++;
            for(size_t i =0;i<line.size();++i)
            {
                if(line[i] == '1')
                {
                    numberOfOnes[i] = numberOfOnes[i]+1;
                }
            }
        }
    }

    std::bitset<12> gamma,  epsilon;
    for(size_t i =0;i < numberOfOnes.size();++i)
    {
        if(numberOfOnes[i] < numberOfLines/2)
        {
            std::bitset<12> mask(2048);
            mask = mask >> i;
            epsilon |= mask;
        }
        else
        {
            std::bitset<12> mask(2048);
            mask = mask >> i;
            gamma |= mask;
        }
    }
    std::cout<<"Gamma: "<<gamma<<" Decimal: "<<gamma.to_ullong()<<std::endl;
    std::cout<<"Epsilon: "<<epsilon<<" Decimal: "<<epsilon.to_ullong()<<std::endl;

    std::cout<<"Multiplied: "<<gamma.to_ullong() * epsilon.to_ullong()<<std::endl;

    return 0;
}
