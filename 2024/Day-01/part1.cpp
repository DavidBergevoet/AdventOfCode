#include <iostream>
#include <vector>
#include <algorithm>

#include "FileHandler.hpp"
#include "Matrix.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);

    std::vector<int> leftList, rightList;   

    if (file.IsOpen())
    {
        // Read the file
        std::vector<uint32_t> splitLine;
        while(file.GetLineSplit(splitLine))
        {
            leftList.push_back(splitLine[0]);
            rightList.push_back(splitLine[1]);
        }
    }

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    uint32_t distance = 0;

    for(size_t i = 0; i < leftList.size(); ++i)
    {
        distance += std::abs(leftList[i]-rightList[i]);
    }

    std::cout<<"Distance: "<<distance<<std::endl;

    return 0;
}