#include <iostream>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";
    std::vector<std::vector<std::string>> fileSeperatedInput;

    int32_t x=0, depth=0, aim=0;

    FileHandler file(filePath);
    if(file.IsOpen())
    {
        std::vector<std::string> currentLine;
        while(file.GetLineSplit(currentLine, " "))
        {
            if(currentLine.size() == 2)
            {
                if(currentLine[0] == "forward")
                {
                    x += std::stoi(currentLine[1]);
                    depth += aim*std::stoi(currentLine[1]);
                }
                else if(currentLine[0] == "down")
                {
                    aim += std::stoi(currentLine[1]);
                }
                else if(currentLine[0] == "up")
                {
                    aim -= std::stoi(currentLine[1]);
                }
            }
            else
            {
                throw std::invalid_argument("Input file isnt correct");
            }
        }
    }
    else
    {
        throw std::invalid_argument("Cannot open input file");
    }

    std::cout<<"Product x*Depth: "<<x*depth<<std::endl;
    
    return 0;
}
