#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

bool IsSorted(const std::vector<int>& rSeparatedLine)
{
  bool isMinusOne = false;
  for (int i : rSeparatedLine)
  {
    if (i == -1)
      isMinusOne = true;
    else if (isMinusOne)
      return false;
  }
  return true;
}

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

  // for (int i : separatedLine)
  //   std::cout << i << ",";
  // std::cout << std::endl;

  while (!IsSorted(separatedLine))
  {
    for (int i = separatedLine.size() - 1; i >= 0; --i)
    {
      if (separatedLine[i] != -1)
      {
        for (int j = 0; j < separatedLine.size(); ++j)
        {
          if (separatedLine[j] == -1)
          {
            separatedLine[j] = separatedLine[i];
            separatedLine[i] = -1;
            break;
          }
        }
        break;
      }
    }
  }
  // for (int i : separatedLine)
  //   std::cout << i << ",";
  // std::cout << std::endl;

  uint64_t result = 0;
  for (int i = 0; i < separatedLine.size(); ++i)
  {
    if (separatedLine[i] != -1)
    {
      result += separatedLine[i] * i;
    }
  }
  std::cout << "Result: " << result << std::endl;
  return 0;
}
