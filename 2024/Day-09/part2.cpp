#include <iostream>
#include <map>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  std::vector<int> separatedLine;
  std::vector<std::pair<int, int>> toSort; // value,size
  std::string line;

  if (file.IsOpen())
  {
    // Read the file
    bool isFreeSpace = false;
    int counter = 0;
    while (file.GetLine(line))
    {
      for (int i = 0; i < line.size(); ++i)
      {
        int value = line[i] - '0';
        if (i % 2 == 0)
          toSort.push_back(std::make_pair(counter, value));
        for (int j = 0; j < value; ++j)
          separatedLine.push_back(isFreeSpace ? -1 : counter);

        if (isFreeSpace)
          counter++;
        isFreeSpace = !isFreeSpace;
      }
    }
  }

  while (toSort.size() > 0)
  {
    const auto& sortPair = toSort[toSort.size() - 1];

    int freeSpace = 0;
    for (int i = 0; i < separatedLine.size(); ++i)
    {
      if (separatedLine[i] == sortPair.first)
      {
        break;
      }
      else if (separatedLine[i] == -1)
      {
        freeSpace++;
        if (freeSpace >= sortPair.second)
        {
          // std::cout << "Found at " << i << ' ' << separatedLine[i] << ' ' << freeSpace << ' ' << sortPair.first << ' ' << sortPair.second << std::endl;
          for (int& rVal : separatedLine)
            if (rVal == sortPair.first)
              rVal = -1;
          for (int j = i - freeSpace + 1; j <= i; ++j)
            separatedLine[j] = sortPair.first;
          break;
        }
      }
      else
      {
        freeSpace = 0;
      }
    }

    toSort.pop_back();
    // break;
  }

  // for (auto i : separatedLine)
  // {
  //   if (i == -1)
  //     std::cout << '.';
  //   else
  //     std::cout << i;
  // }
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
