#include <iostream>
#include <vector>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    uint64_t totalPoints = 0;

    FileHandler file(filePath);
    if (file.IsOpen())
    {
        // Read the file
        std::string line;
        while (file.GetLine(line))
        {
            std::string firstPart = line.substr(0,line.size()/2);
            std::string secondPart = line.substr(line.size()/2);

            for(const char& rChar : firstPart)
            {
                if(secondPart.find(rChar) != std::string::npos)
                {
                    if(rChar >= 'a')
                    {
                        totalPoints += rChar - 'a' + 1;
                    }
                    else
                    {
                        totalPoints += rChar - 'A' + 27;
                    }
                    break;
                }
            }
        }
    }
    std::cout<<"Totalpoints: "<<totalPoints<<std::endl;
    return 0;
}