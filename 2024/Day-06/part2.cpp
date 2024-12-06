#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

enum class Direction_e
{
  UP = 0,
  RIGHT = 1,
  DOWN = 2,
  LEFT = 3
};

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  Matrix<bool> map, mapCopy;
  Point_t guardy;

  if (file.IsOpen())
  {
    // Read the file
    std::string line;
    while (file.GetLine(line))
    {
      if (map.GetColumns() != line.size())
        map.Resize(0, line.size());

      std::vector<bool> row;
      for (int i = 0; i < line.size(); ++i)
      {
        row.push_back(line[i] == '#');
        if (line[i] == '^')
          guardy = MakePoint(map.GetRows() + 1, i);
      }
      map.AddRow(row);
    }
  }

  int obstacles = 0;
  int counter = 0;
  for (const Point_t& rPoint : map.GetAllPoints())
  {
    std::cout << "Count: " << counter++ << " of " << map.GetAllPoints().size() << std::endl;
    Direction_e dir = Direction_e::UP;
    Matrix<bool> mapCopy = map;
    mapCopy[rPoint.first][rPoint.second] = true;
    Point_t guardCopy = guardy;

    std::vector<std::pair<Point_t, Direction_e>> path;
    bool guardIsInside = true;
    bool guardLoop = false;

    while (guardIsInside && !guardLoop)
    {
      for (const std::pair<Point_t, Direction_e>& rPathPoint : path)
      {
        if (rPathPoint.first == guardCopy && rPathPoint.second == dir)
        {
          guardLoop = true;
          obstacles++;
          break;
        }
      }
      path.push_back(std::make_pair(guardCopy, dir));
      if (guardLoop)
        break;

      switch (dir)
      {
      case Direction_e::UP:
        guardCopy.first--;
        break;
      case Direction_e::RIGHT:
        guardCopy.second++;
        break;
      case Direction_e::DOWN:
        guardCopy.first++;
        break;
      case Direction_e::LEFT:
        guardCopy.second--;
        break;
      }

      for (const Point_t& rPoint : mapCopy.GetOutsidePoints())
      {
        if (rPoint.first == guardCopy.first && rPoint.second == guardCopy.second)
        {
          guardIsInside = false;
          break;
        }
      }
      if (guardIsInside)
      {
        switch (dir)
        {
        case Direction_e::UP:
          if (mapCopy[guardCopy.first - 1][guardCopy.second])
            dir = Direction_e::RIGHT;
          break;
        case Direction_e::RIGHT:
          if (mapCopy[guardCopy.first][guardCopy.second + 1])
            dir = Direction_e::DOWN;
          break;
        case Direction_e::DOWN:
          if (mapCopy[guardCopy.first + 1][guardCopy.second])
            dir = Direction_e::LEFT;
          break;
        case Direction_e::LEFT:
          if (mapCopy[guardCopy.first][guardCopy.second - 1])
            dir = Direction_e::UP;
          break;
        }
      }
    }
  }
  std::cout << "obs: " << obstacles << std::endl;
  return 0;
}
