#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

std::vector<std::pair<uint, uint>> rules;

int CheckPages(const std::vector<uint>& rPages)
{
  int returnValue = 0;
  bool valid = true;
  for (int i = 0; i < rPages.size() - 1; ++i)
  {
    bool ruleFound = false;
    for (const auto& rRule : rules)
    {
      if (rRule.first == rPages[i] && rRule.second == rPages[i + 1])
      {
        ruleFound = true;
        break;
      }
    }
    if (!ruleFound)
    {
      valid = false;
      break;
    }
  }

  if (valid)
    returnValue = rPages[rPages.size() / 2];

  std::cout << "Return: " << returnValue << std::endl;

  return returnValue;
}

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  uint total = 0;
  if (file.IsOpen())
  {
    bool parsingRules = true;
    std::string separator = "|";
    // Read the file
    std::vector<uint> lineSplit;

    uint lineCount = 0;
    while (file.GetLineSplit(lineSplit, separator))
    {
      if (lineSplit.empty())
      {
        parsingRules = false;
        separator = ",";
      }

      if (parsingRules)
      {
        rules.push_back(std::make_pair(lineSplit[0], lineSplit[1]));
      }
      else
      {
        std::cout << "Line: " << lineCount++ << std::endl;
        total += CheckPages(lineSplit);
      }
    }
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}
