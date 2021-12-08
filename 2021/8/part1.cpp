#include <iostream>
#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");
    std::vector<std::string> splitLine;

    uint32_t digitCount = 0;

    while(file.GetLineSplit(splitLine, " | "))
    {
        // std::cout<<splitLine[1]<<std::endl;
        std::vector<std::string> innerSplitLine = FileHandler::SplitString(splitLine[1], " ");
        for(const std::string& rDigit : innerSplitLine)
        {
            // std::cout<<"\t'"<<rDigit<<"'"<<std::endl;
            size_t digitLength = rDigit.length();
            if((digitLength == 2)/*1*/ || (digitLength == 3)/*7*/ || (digitLength == 4)/*4*/ || (digitLength == 7)/*8*/)
                digitCount++;
        }
    }
    std::cout<<"Total digits: "<<digitCount<<std::endl;

    return 0;
}
