#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

Matrix<char> fileMatrix;

int CheckMas(Point_t point)
{
  std::vector<Point_t> mPoints;
  std::vector<Point_t> sPoints;
  for (Point_t adjPoint : fileMatrix.GetAdjacentPoints(point, true))
  {
    if (adjPoint.first != point.first && adjPoint.second != point.second) // Only diagonal
    {
      if (fileMatrix[adjPoint] == 'M')
      {
        mPoints.push_back(adjPoint);
      }
      else if (fileMatrix[adjPoint] == 'S')
      {
        sPoints.push_back(adjPoint);
      }
    }
  }
  bool valid = false;
  if (mPoints.size() == 2 && sPoints.size() == 2)
  {
    if (mPoints[0].first == mPoints[1].first || mPoints[0].second == mPoints[1].second)
    {
      valid = true;
    }
  }
  return valid ? 1 : 0;
}

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  if (file.IsOpen())
  {
    // Read the file
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

    int masses = 0;
    for (Point_t point : fileMatrix.GetAllPoints())
    {
      if (fileMatrix[point] == 'A')
      {
        masses += CheckMas(point);
      }
    }
    std::cout << "Masses " << masses << std::endl;
  }
  return 0;
}
