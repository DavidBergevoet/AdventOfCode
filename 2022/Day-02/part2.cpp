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
            std::vector<std::string> splitString = file.SplitString(line, " ");

            if (splitString[1] == "X") // Lose
            {
                if(splitString[0] == "A")
                {
                    totalPoints += 3;
                }
                else if(splitString[0] == "B")
                {
                    totalPoints += 1;
                }
                else if(splitString[0] == "C")
                {
                    totalPoints += 2;
                }
            }
            else if (splitString[1] == "Y") // Draw
            {
                totalPoints += 3;

                if(splitString[0] == "A")
                {
                    totalPoints += 1;
                }
                else if(splitString[0] == "B")
                {
                    totalPoints += 2;
                }
                else if(splitString[0] == "C")
                {
                    totalPoints += 3;
                }
            }
            else if (splitString[1] == "Z") // Win
            {
                totalPoints += 6;

                if(splitString[0] == "A")
                {
                    totalPoints += 2;
                }
                else if(splitString[0] == "B")
                {
                    totalPoints += 3;
                }
                else if(splitString[0] == "C")
                {
                    totalPoints += 1;
                }
            }
        }
    }
    std::cout << "Total points: " << totalPoints << std::endl;
}