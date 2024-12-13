#include <climits>
#include <iostream>
#include <regex>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

typedef struct
{
  uint aX;
  uint aY;
  uint bX;
  uint bY;
  uint64_t destX;
  uint64_t destY;
} ClawMachine_t;

typedef struct
{
  uint64_t aPresses;
  uint64_t restValueX;
  uint64_t restValueY;
} PossibleOutcome_t;

const uint A_PRESSES_TOKENS = 3;
const uint B_PRESSES_TOKENS = 1;

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  std::vector<ClawMachine_t> machines;

  if (file.IsOpen())
  {
    // Read the file
    std::vector<std::string> line;
    bool isAButton = true;
    ClawMachine_t tempClawMachine;
    while (file.GetLineSplit(line))
    {
      if (line.size() == 4) // Button
      {
        if (isAButton)
        {
          isAButton = false;
          tempClawMachine.aX = std::stoul(line[2].substr(2));
          tempClawMachine.aY = std::stoul(line[3].substr(2));
        }
        else
        {
          isAButton = true;
          tempClawMachine.bX = std::stoul(line[2].substr(2));
          tempClawMachine.bY = std::stoul(line[3].substr(2));
        }
      }
      else if (line.size() == 3) // Prize
      {
        tempClawMachine.destX = std::stoull(line[1].substr(2)) + 10000000000000;
        tempClawMachine.destY = std::stoull(line[2].substr(2)) + 10000000000000;
        machines.push_back(tempClawMachine);
      }
    }
  }

  uint totalTokens = 0;

  for (int i = 0; i < machines.size(); ++i)
  {
    std::cout << i << ' ' << machines[i].aX << ' ' << machines[i].aY << ' ' << machines[i].bX << ' ' << machines[i].bY << ' ' << machines[i].destX << ' '
              << machines[i].destY << std::endl;

    int64_t restValueX = machines[i].destX, restValueY = machines[i].destY;
    std::vector<PossibleOutcome_t> aPressValues;
    uint64_t aPresses = 0;
    while (restValueX >= 0 && restValueY >= 0)
    {
      if (aPresses % 10000000 == 0)
        std::cout << restValueX << ' ' << restValueY << std::endl;
      if (restValueX % machines[i].bX == 0 && restValueY % machines[i].bY == 0 && restValueX / machines[i].bX == restValueY / machines[i].bY)
      {
        aPressValues.push_back(PossibleOutcome_t{aPresses, (uint64_t)restValueX, (uint64_t)restValueY});
      }
      restValueX -= (int64_t)machines[i].aX;
      restValueY -= (int64_t)machines[i].aY;
      aPresses++;
    }
    uint64_t leastTokens = UINT64_MAX;
    for (const PossibleOutcome_t& rOutcome : aPressValues)
    {
      std::cout << rOutcome.aPresses << ' ' << (rOutcome.restValueX / machines[i].bX) << std::endl;
      uint tokens = rOutcome.aPresses * A_PRESSES_TOKENS;
      uint64_t bPresses = (rOutcome.restValueX / machines[i].bX);
      tokens += bPresses * B_PRESSES_TOKENS;
      if (tokens < leastTokens)
        leastTokens = tokens;
    }

    std::cout << "Least tokens: " << leastTokens << std::endl;
    if (leastTokens != UINT64_MAX)
      totalTokens += leastTokens;

    // break;
  }

  std::cout << "Total " << totalTokens << std::endl;

  return 0;
}
