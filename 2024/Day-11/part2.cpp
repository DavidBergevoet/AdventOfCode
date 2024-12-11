#include <iostream>
#include <map>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

std::map<uint64_t, uint64_t> numberMap;

void Blink(uint blink)
{
  std::map<uint64_t, uint64_t> newNumber;
  for (const auto& i : numberMap)
  {
    uint64_t stoneValue = i.first;
    std::string stoneString = std::to_string(stoneValue);
    if (stoneValue == 0)
    {
      newNumber[1] += i.second;
    }
    else if (stoneString.size() % 2 == 0)
    {
      uint64_t lhs = std::stoull(stoneString.substr(0, stoneString.size() / 2));
      uint64_t rhs = std::stoull(stoneString.substr(stoneString.size() / 2));

      newNumber[lhs] += i.second;
      newNumber[rhs] += i.second;
    }
    else
    {
      newNumber[i.first * 2024] += i.second;
    }
  }
  numberMap = newNumber;
}

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  if (file.IsOpen())
  {
    // Read the file
    std::vector<uint64_t> stones;
    if (file.GetLineSplit(stones))
    {
      for (auto stone : stones)
        numberMap[stone]++;
    }
  }

  int BLINKING = 75;
  for (int i = 0; i < BLINKING; ++i)
  {
    std::cout << "Blink " << i << " of " << BLINKING << std::endl;
    Blink(i);
  }

  uint64_t total = 0;
  for (auto i : numberMap)
  {
    total += i.second;
    // std::cout << "N: " << i.first << " " << i.second << std::endl;
  }
  std::cout << "Total: " << total << std::endl;
  return 0;
}
