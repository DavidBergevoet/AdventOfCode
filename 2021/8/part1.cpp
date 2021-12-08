#include <iostream>
#include "FileHandler.hpp"

std::vector<std::string> SplitString(const std::string& rInput, const std::string& rSeperator)
{
    std::vector<std::string> returnVector;
    size_t pos = 0;
    std::string part, inputCopy = rInput;
    while((pos = inputCopy.find(rSeperator)) != std::string::npos)
    {
        part = inputCopy.substr(0, pos);
        inputCopy.erase(0, pos + rSeperator.length());
        returnVector.push_back(part);
    }
    if(inputCopy != "")
        returnVector.push_back(inputCopy);
    
    return returnVector;
}

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");
    std::vector<std::string> splitLine;

    uint32_t digitCount = 0;

    while(file.GetLineSplit(splitLine, " | "))
    {
        // std::cout<<splitLine[1]<<std::endl;
        std::vector<std::string> innerSplitLine = SplitString(splitLine[1], " ");
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
