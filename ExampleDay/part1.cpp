#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);

    if (file.IsOpen())
    {
        // Read the file
        std::string line;
        while(file.GetLine(line))
        {
        }
    }
    return 0;
}