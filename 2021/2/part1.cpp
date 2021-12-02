#include <iostream>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);
    int32_t x = 0, depth = 0;

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
                }
                else if(currentLine[0] == "down")
                {
                    depth += std::stoi(currentLine[1]);
                }
                else if(currentLine[0] == "up")
                {
                    depth -= std::stoi(currentLine[1]);
                }
            }
            else
            {
                throw std::invalid_argument("Input file isnt correct");
            }
        }
        std::cout<<"Product x*depth: "<<x*depth<<std::endl;
    }

    return 0;
}
