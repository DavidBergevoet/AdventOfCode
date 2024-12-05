#include <algorithm>
#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

std::vector<std::pair<uint, uint>> rules;

bool CheckPages(const std::vector<uint>& rPages)
{
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

  return valid;
}

int OrderPages(std::vector<uint> pages)
{
  // for (auto i : pages)
  //   std::cout << i << ',';
  // std::cout << std::endl;

  for (int i = 0; i < pages.size() - 1; ++i)
  {
    for (const auto& rRule : rules)
    {
      if (rRule.first == pages[i + 1] && rRule.second == pages[i])
      {
        std::iter_swap(pages.begin() + i, pages.begin() + i + 1);
        return OrderPages(pages);
      }
    }
  }
  // std::cout << "Returning " << pages[pages.size() / 2] << std::endl;
  return pages[pages.size() / 2];
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
      else if (!lineSplit.empty())
      {
        // std::cout << "Line: " << lineCount++ << std::endl;
        bool valid = CheckPages(lineSplit);
        if (!valid)
          total += OrderPages(lineSplit);
      }
    }
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}
