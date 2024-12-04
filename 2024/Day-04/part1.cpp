#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

Matrix<char> fileMatrix;
const std::string wordToFind = "XMAS";

int FindWord(int row, int column, int charIndex, int horizontal, int vertical)
{
  int returnValue = 0;
  if (fileMatrix[row][column] == wordToFind[charIndex])
  {
    if (charIndex == wordToFind.size() - 1)
    {
      return 1;
    }
    else
    {
      for (Point_t p : fileMatrix.GetAdjacentPoints(std::make_pair(row, column), true))
      {
        if (p.first == row + vertical && p.second == column + horizontal)
        {
          returnValue += FindWord(p.first, p.second, charIndex + 1, horizontal, vertical);
        }
      }
    }
  }
  return returnValue;
}

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  if (file.IsOpen())
  {
    // Read the file
    std::string line;
    while (file.GetLine(line))
    {
      if (line.size() != fileMatrix.GetColumns())
      {
        fileMatrix.Resize(0, line.size());
      }
      std::vector<char> lineChars;
      for (auto c : line)
      {
        lineChars.push_back(c);
      }
      fileMatrix.AddRow(lineChars);
    }

    // std::cout << fileMatrix << std::endl;

    int words = 0;
    for (int r = 0; r < fileMatrix.GetRows(); ++r)
    {
      for (int c = 0; c < fileMatrix.GetColumns(); ++c)
      {
        words += FindWord(r, c, 0, 1, 0);   // Left -> right
        words += FindWord(r, c, 0, -1, 0);  // Right -> left
        words += FindWord(r, c, 0, 0, 1);   // Top -> bottom
        words += FindWord(r, c, 0, 0, -1);  // Bottom -> top
        words += FindWord(r, c, 0, 1, 1);   // Top left -> bottom right
        words += FindWord(r, c, 0, -1, -1); // Bottom right -> top left
        words += FindWord(r, c, 0, 1, -1);  // Bottom left -> top right
        words += FindWord(r, c, 0, -1, 1);  // Top right -> bottom left
      }
    }
    std::cout << "Words " << words << std::endl;
  }

  return 0;
}
