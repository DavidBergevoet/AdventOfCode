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
        std::cout << i << ',';
      std::cout << std::endl;
      bool errorHappened = false;

      bool safe = true;

      std::vector<uint32_t> ascCheck = splitLine, descCheck = splitLine;
      std::sort(ascCheck.begin(), ascCheck.end());
      std::sort(descCheck.begin(), descCheck.end(), std::greater<uint32_t>());

      int ascDiffs = 0, descDiffs = 0;
      for (int i = 0; i < ascCheck.size(); ++i)
      {
        if (ascCheck[i] != splitLine[i])
          ascDiffs++;
      }
      for (int i = 0; i < descCheck.size(); ++i)
      {
        if (descCheck[i] != splitLine[i])
          descDiffs++;
      }
      std::cout << "D: " << ascDiffs << ' ' << descDiffs;

      if (ascDiffs == 1 || descDiffs == 1)
        errorHappened = true;
      else if (ascDiffs > 1 && descDiffs > 1)
        safe = false;

      if (safe)
      {
        for (int i = 0; i < splitLine.size() - 1; ++i)
        {
          uint32_t diff = std::abs((int)splitLine[i] - (int)splitLine[i + 1]);
          std::cout << '\t' << diff << ' ' << splitLine[i] << ' ' << splitLine[i + 1] << ' ' << errorHappened << std::endl;
          if (diff > 3 || diff < 1)
          {
            if (errorHappened)
            {
              safe = false;
              break;
            }
            errorHappened = true;
          }
        }
      }
      if (safe)
        safeLines++;
      counter++;
    }
  }
  std::cout << "Safe lines: " << safeLines << std::endl;
  return 0;
}
