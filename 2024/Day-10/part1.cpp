#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

Matrix<int64_t> map;
std::vector<Point_t> ninesVisited;

int SearchPath(const Point_t& rPoint, std::vector<Point_t> path)
{
  int returnValue = 0;
  for (const Point_t& rPathPoint : path)
  {
    if (rPoint == rPathPoint)
      return 0;
  }
  path.push_back(rPoint);

  if (map[rPoint] == 9)
  {
    int index = -1;
    for (int i = 0; i < ninesVisited.size(); ++i)
    {
      if (ninesVisited[i] == rPoint)
      {
        index = i;
        break;
      }
    }

    if (index != -1)
    {
      ninesVisited.erase(ninesVisited.begin() + index);
      return 1;
    }
  }
  else
  {
    std::vector<Point_t> adjPoints = map.GetAdjacentPoints(rPoint, false);
    for (const Point_t& rAdjPoint : adjPoints)
    {
      // std::cout << map[rAdjPoint] << ' ' << map[rPoint] << ' ' << map[rAdjPoint] - map[rPoint] << std::endl;
      if (map[rAdjPoint] - map[rPoint] == 1)
      {
        // std::cout << "\tIN\n";
        returnValue += SearchPath(rAdjPoint, path);
      }
    }
  }
  return returnValue;
}

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  std::vector<Point_t> zeroPositions;
  std::vector<Point_t> ninePositions;

  if (file.IsOpen())
  {
    // Read the file
    std::string line;
    while (file.GetLine(line))
    {
      if (map.GetColumns() != line.size())
        map.Resize(0, line.size());

      std::vector<int64_t> lineSplit;
      for (char c : line)
      {
        int64_t value = c == '.' ? -1 : c - '0';
        lineSplit.push_back(value);
        if (value == 0)
        {
          zeroPositions.push_back(MakePoint(map.GetRows(), lineSplit.size() - 1));
        }
        else if (value == 9)
        {
          ninePositions.push_back(MakePoint(map.GetRows(), lineSplit.size() - 1));
        }
      }
      map.AddRow(lineSplit);
    }
  }

  int result = 0;
  for (auto i : zeroPositions)
  {
    ninesVisited = ninePositions;
    std::vector<Point_t> path;
    result += SearchPath(i, path);
  }

  std::cout << "Result: " << result << std::endl;

  return 0;
}
