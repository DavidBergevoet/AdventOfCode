#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  std::vector<int> separatedLine;

  if (file.IsOpen())
  {
    // Read the file
    std::string line;
    bool isFreeSpace = false;
    int counter = 0;
    while (file.GetLine(line))
    {
      for (int i = 0; i < line.size(); ++i)
      {
        int value = line[i] - '0';
        for (int j = 0; j < value; ++j)
          separatedLine.push_back(isFreeSpace ? -1 : counter);

        if (isFreeSpace)
          counter++;
        isFreeSpace = !isFreeSpace;
      }
    }
  }

  return 0;
}
