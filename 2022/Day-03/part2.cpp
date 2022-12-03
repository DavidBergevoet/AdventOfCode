#include <iostream>
#include <vector>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    uint64_t totalPoints = 0;

    std::vector<std::string> elfVector(3);

    FileHandler file(filePath);
    uint counter = 0;
    if (file.IsOpen())
    {
        // Read the file
        std::string line;
        while (file.GetLine(line))
        {
            elfVector[counter] = line;
            counter++;

            if(counter == 3)
            {
                for(const char& rChar : elfVector[0])
                {
                    if(elfVector[1].find(rChar) != std::string::npos && elfVector[2].find(rChar) != std::string::npos)
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
                counter = 0;
            }
        }
    }

    std::cout<<"TotalPoints: "<<totalPoints<<std::endl;
    return 0;
}