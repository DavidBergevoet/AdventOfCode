#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

std::vector<uint64_t> stones;

void Blink()
{
  for (int i = 0; i < stones.size(); ++i)
  {
    std::string stoneString = std::to_string(stones[i]);
    if (stones[i] == 0)
    {
      stones[i] = 1;
    }
    else if (stoneString.size() % 2 == 0)
    {
      uint64_t lhs = std::stoull(stoneString.substr(0, stoneString.size() / 2));
      uint64_t rhs = std::stoull(stoneString.substr(stoneString.size() / 2));

      stones[i] = lhs;
      stones.insert(stones.begin() + i + 1, rhs);
      i++;
    }
    else
    {
      stones[i] *= 2024;
    }
  }
}

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  if (file.IsOpen())
  {
    // Read the file
    if (file.GetLineSplit(stones))
    {
    }
  }

  int BLINKING = 25;
  for (int i = 0; i < BLINKING; ++i)
  {
    Blink();
  }

  for (auto i : stones)
  {
    // std::cout << '\t' << i << std::endl;
  }

  std::cout << "Number of stones: " << stones.size() << std::endl;
  return 0;
}
