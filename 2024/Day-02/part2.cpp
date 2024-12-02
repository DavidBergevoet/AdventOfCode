#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "FileHandler.hpp"

bool isSafe(std::vector<uint32_t> line)
{
  bool desc = line[0] > line[1];
  int prev = line[0] + (desc ? 1 : -1);

  for (int col : line)
  {
    if (desc)
    {
      if (col >= prev || (prev - col) > 3)
      {
        return false;
      }
    }
    else
    {
      if (col <= prev || (col - prev) > 3)
      {
        return false;
      }
    }
    prev = col;
  }
  return true;
}

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  int safeLines = 0;
  if (file.IsOpen())
  {
    std::vector<uint32_t> splitLine;

    while (file.GetLineSplit(splitLine))
    {
      // Initial check for safety
      if (isSafe(splitLine))
      {
        safeLines++;
        continue;
      }

      // Try removing one level at a time
      bool lineIsSafe = false;
      for (size_t i = 0; i < splitLine.size(); ++i)
      {
        std::vector<uint32_t> modifiedLine = splitLine;
        modifiedLine.erase(modifiedLine.begin() + i);

        if (isSafe(modifiedLine))
        {
          lineIsSafe = true;
          break;
        }
      }

      if (lineIsSafe)
      {
        safeLines++;
      }
    }
  }

  std::cout << "Safe lines: " << safeLines << std::endl;
  return 0;
}
