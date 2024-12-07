#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

enum class Operator_e
{
  MINUS,
  DIVIDE,
  CONCATENATION
};
const std::vector<Operator_e> OPERATORS{Operator_e::MINUS, Operator_e::DIVIDE, Operator_e::CONCATENATION};

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  std::vector<std::pair<uint64_t, std::vector<uint64_t>>> numberList;

  if (file.IsOpen())
  {
    // Read the file
    std::vector<uint64_t> line;
    while (file.GetLineSplit(line))
    {
      std::pair<uint64_t, std::vector<uint64_t>> lineValues;
      lineValues.first = line[0];
      for (int i = 1; i < line.size(); ++i)
        lineValues.second.push_back(line[i]);
      numberList.push_back(lineValues);
    }
  }

  uint64_t total = 0;

  int counter = 0;
  for (const auto& rNumber : numberList)
  {
    // if (counter++ > 2)
    //   break;
    // std::cout << "---------\n" << rNumber.first << "\n-------\n" << std::endl;
    std::vector<uint64_t> calculatedNumbers;
    std::vector<uint64_t> newNumbers;
    calculatedNumbers.push_back(rNumber.first);

    for (int i = rNumber.second.size() - 1; i > 0; --i)
    {
      // std::cout << "i " << rNumber.second[i] << std::endl;
      newNumbers.clear();

      for (auto c : calculatedNumbers)
      {
        // std::cout << "C: " << c << std::endl;
        for (auto op : OPERATORS)
        {
          uint64_t result = UINT64_MAX;
          switch (op)
          {
          case Operator_e::DIVIDE:
            if (c % rNumber.second[i] == 0)
              result = c / rNumber.second[i];
            break;
          case Operator_e::MINUS:
            if (rNumber.second[i] < c)
              result = c - rNumber.second[i];
            break;
          case Operator_e::CONCATENATION:
            std::string rhs = std::to_string(rNumber.second[i]);
            std::string lhs = std::to_string(rNumber.second[i - 1]);
            std::string calcString = std::to_string(c);
            if (calcString.size() >= rhs.size() + lhs.size() && rhs == calcString.substr(calcString.size() - rhs.size()))
            {
              result = std::stoull(calcString.substr(0, calcString.size() - rhs.size()));
              // std::cout << lhs << "\t" << rhs << '\t' << calcString << '\t' << result << std::endl;
            }
            break;
          }
          // std::cout << "Result: " << (int)op << ' ' << result << std::endl;

          if (result != UINT64_MAX)
          {
            newNumbers.push_back(result);
            // std::cout << "Adding " << result << std::endl;
          }
        }
      }
      calculatedNumbers = newNumbers;
    }
    for (auto c : calculatedNumbers)
    {
      if (c == rNumber.second[0])
      {
        total += rNumber.first;
        // std::cout << "Appending to total" << std::endl;
        break;
      }
    }
  }

  std::cout << "Total: " << total << std::endl;
  return 0;
}
