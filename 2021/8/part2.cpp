#include <iostream>
#include "FileHandler.hpp"

std::vector<std::string> discoveredNumbers;

void PrintDiscoveredNumbers()
{
    std::cout<<"Discovered:"<<std::endl;
    for(size_t i = 0; i < discoveredNumbers.size(); ++i)
    {
        std::cout<<i<<"\t'"<<discoveredNumbers[i]<<"'"<<std::endl;
    }
}

bool StringContains(const std::string& rInput, const std::string& rContain)
{
    std::vector<bool> containValues;
    containValues.resize(rContain.length());

    for(char inputChar : rInput)
    {
        for(size_t i = 0; i < rContain.length(); ++i)
        {
            if(inputChar == rContain[i])
                containValues[i] = true;
        }
    }

    for(bool value : containValues)
    {
        if(!value)
            return false;
    }
    return true;
}

bool StringContainsExact(const std::string& rInput, const std::string& rContain)
{
    if(rInput.length() != rContain.length())
        return false;

    std::vector<bool> containValues;
    containValues.resize(rInput.length());

    for(char containChar : rContain)
    {
        for(size_t i = 0; i < rInput.length(); ++i)
        {
            if(containChar == rInput[i])
                containValues[i] = true;
        }
    }

    for(bool value : containValues)
    {
        if(!value)
            return false;
    }
    return true;
}

void GetPredefinedNumbers(const std::vector<std::string>& rNumbers)
{
    for(const std::string& number : rNumbers)
    {
        switch(number.length())
        {
            case 2:
                discoveredNumbers[1] = number;
                break;
            case 4:
                discoveredNumbers[4] = number;
                break;
            case 3:
                discoveredNumbers[7] = number;
                break;
            case 7:
                discoveredNumbers[8] = number;
                break;
        }
    }
}

void GetThree(const std::vector<std::string>& rNumbers)
{
    for(const std::string& number : rNumbers)
    {
        if(StringContains(number, discoveredNumbers[7]) && number.size() == 5)
            discoveredNumbers[3] = number;
    }
}

void GetNine(const std::vector<std::string>& rNumbers)
{
    for(const std::string& number : rNumbers)
    {
        if(StringContains(number, discoveredNumbers[3]) && number.size() == 6)
            discoveredNumbers[9] = number;
    }
}

void GetSix(const std::vector<std::string>& rNumbers)
{
    for(const std::string& number : rNumbers)
    {
        if(!StringContains(number, discoveredNumbers[1]) && number.length() == 6)
            discoveredNumbers[6] = number;
    }
}

void GetFive(const std::vector<std::string>& rNumbers)
{
    for(const std::string& number : rNumbers)
    {
        if(StringContains(discoveredNumbers[6],number) && number.length() == 5)
            discoveredNumbers[5] = number;
    }
}

void GetTwo(const std::vector<std::string>& rNumbers)
{
    for(const std::string& number : rNumbers)
    {
        if(number.length() == 5 && number != discoveredNumbers[3] && number != discoveredNumbers[5])
            discoveredNumbers[2] = number;
    }
}

void GetZero(const std::vector<std::string>& rNumbers)
{
    for(const std::string& number : rNumbers)
    {
        if(number.length() == 6 && number != discoveredNumbers[6] && number != discoveredNumbers[9])
            discoveredNumbers[0] = number;
    }
}

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");

    std::vector<std::string> splitLine;
    uint64_t finalResult = 0;
    while(file.GetLineSplit(splitLine, " | "))
    {
        std::vector<std::string> numberList = FileHandler::SplitString(splitLine[0], " ");
        
        discoveredNumbers.clear();
        discoveredNumbers.resize(10);

        // Extract every number
        GetPredefinedNumbers(numberList);
        // PrintDiscoveredNumbers();
        GetThree(numberList);
        GetNine(numberList);
        GetSix(numberList);
        GetFive(numberList);
        GetTwo(numberList);
        GetZero(numberList);
        // PrintDiscoveredNumbers();

        // Calculate the end number
        std::vector<std::string> lineNumberList = FileHandler::SplitString(splitLine[1], " ");
        std::string endNumberString;
        for(const std::string& numberString : lineNumberList)
        {
            for(size_t i = 0; i < discoveredNumbers.size(); ++i)
            {
                if(StringContainsExact(numberString, discoveredNumbers[i]))
                {
                    endNumberString.append(std::to_string(i));
                }
            }
        }
        finalResult += std::stoull(endNumberString);
    }

    std::cout<<"Final result: "<<finalResult<<std::endl;
    return 0;
}
