#include <iostream>
#include <vector>

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

    uint32_t distance = 0;
    for(size_t i = 0; i < leftList.size(); ++i)
    {
        uint32_t occurrences = 0;
        for(size_t j = 0; j < rightList.size(); ++j)
        {
            if(leftList[i] == rightList[j])
            {
                occurrences++;
            }
        }
        distance += leftList[i] * occurrences;
    }

    std::cout<<"Distance: "<<distance<<std::endl;

    return 0;
}