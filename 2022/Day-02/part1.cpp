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

            if (splitString[1] == "X")
            {
                totalPoints += 1;

                if (splitString[0] == "A") // Draw
                {
                    totalPoints += 3;
                }
                else if (splitString[0] == "C") // Win
                {
                    totalPoints += 6;
                }
            }
            else if (splitString[1] == "Y")
            {
                totalPoints += 2;

                if (splitString[0] == "B") // Draw
                {
                    totalPoints += 3;
                }
                else if (splitString[0] == "A") // Win
                {
                    totalPoints += 6;
                }
            }
            else if (splitString[1] == "Z")
            {
                totalPoints += 3;

                if (splitString[0] == "C") // Draw
                {
                    totalPoints += 3;
                }
                else if (splitString[0] == "B") // Win
                {
                    totalPoints += 6;
                }
            }
        }
    }
    std::cout << "Total points: " << totalPoints << std::endl;
}