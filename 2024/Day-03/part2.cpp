#include <iostream>
#include <regex>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  const std::string enabledString = "do()";
  const std::string disableString = "don't()";

  if (file.IsOpen())
  {
    std::regex mulRegex("(?:mul\\((\\d+),(\\d+)\\))|(?:do\\(\\))|(?:don't\\(\\))");

    // Read the file
    std::string line;
    uint32_t val = 0;
    bool enabled = true;
    while (file.GetLine(line))
    {
      std::sregex_iterator begin{line.begin(), line.end(), mulRegex};
      std::sregex_iterator end;
      for (std::sregex_iterator it = begin; it != end; ++it)
      {
        std::smatch match = *it;
        std::cout << "Full match: " << match.str(0) << std::endl;
        if (match.str(0) == enabledString)
        {
          enabled = true;
        }
        else if (match.str(0) == disableString)
        {
          enabled = false;
        }
        else
        {
          if (enabled)
            val += std::stoi(match.str(1)) * std::stoi(match.str(2));
        }
      }
    }
    std::cout << "Value: " << val << std::endl;
  }
  return 0;
}
