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

  Matrix<bool> map;
  Point_t guard;
  Direction_e dir = Direction_e::UP;

  std::vector<Point_t> path;

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
          guard = MakePoint(map.GetRows() + 1, i);
      }
      map.AddRow(row);
    }
  }

  bool guardIsInside = true;
  while (guardIsInside)
  {
    bool contains = false;
    for (const Point_t& rPoint : path)
    {
      if (rPoint == guard)
      {
        contains = true;
        break;
      }
    }
    if (!contains)
      path.push_back(guard);

    switch (dir)
    {
    case Direction_e::UP:
      guard.first--;
      break;
    case Direction_e::RIGHT:
      guard.second++;
      break;
    case Direction_e::DOWN:
      guard.first++;
      break;
    case Direction_e::LEFT:
      guard.second--;
      break;
    }

    for (const Point_t& rPoint : map.GetOutsidePoints())
    {
      if (rPoint.first == guard.first && rPoint.second == guard.second)
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
        if (map[guard.first - 1][guard.second])
          dir = Direction_e::RIGHT;
        break;
      case Direction_e::RIGHT:
        if (map[guard.first][guard.second + 1])
          dir = Direction_e::DOWN;
        break;
      case Direction_e::DOWN:
        if (map[guard.first + 1][guard.second])
          dir = Direction_e::LEFT;
        break;
      case Direction_e::LEFT:
        if (map[guard.first][guard.second - 1])
          dir = Direction_e::UP;
        break;
      }
    }
  }
  path.push_back(guard);

  std::cout << "Path " << path.size() << std::endl;
  return 0;
}
