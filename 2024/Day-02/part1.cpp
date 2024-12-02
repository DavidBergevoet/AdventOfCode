#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  int safeLines = 0;
  if (file.IsOpen())
  {
    // Read the file
    std::vector<uint32_t> splitLine;
    int counter = 0;
    while (file.GetLineSplit(splitLine))
    {
      std::cout << counter << std::endl;
      for (auto i : splitLine)
      {
        std::cout << i << ',';
      }
      std::cout << std::endl;

      bool safe = true;

      std::vector<uint32_t> ascCheck = splitLine, descCheck = splitLine;
      std::sort(ascCheck.begin(), ascCheck.end());
      std::sort(descCheck.begin(), descCheck.end(), std::greater<uint32_t>());
      if (splitLine != ascCheck && splitLine != descCheck)
        safe = false;

      if (safe)
      {
        for (int i = 0; i < splitLine.size() - 1; ++i)
        {
          uint32_t diff = std::abs((int)splitLine[i] - (int)splitLine[i + 1]);
          std::cout << '\t' << diff << ' ' << splitLine[i] << ' ' << splitLine[i + 1] << std::endl;
          if (diff > 3 || diff < 1)
          {
            safe = false;
            break;
          }
        }
      }
      if (safe)
        safeLines++;
    }
  }
  std::cout << "Safe lines: " << safeLines << std::endl;
  return 0;
}
