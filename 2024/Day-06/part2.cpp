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

std::vector<Point_t> part1(Point_t guard, const Matrix<bool>& rMap)
{
  std::vector<Point_t> path;
  Direction_e dir = Direction_e::UP;
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

    for (const Point_t& rPoint : rMap.GetOutsidePoints())
    {
      if (rPoint.first == guard.first && rPoint.second == guard.second)
      {
        guardIsInside = false;
        break;
      }
    }
    if (!guardIsInside)
      break;

    switch (dir)
    {
    case Direction_e::UP:
      if (rMap[guard.first - 1][guard.second])
        dir = Direction_e::RIGHT;
      break;
    case Direction_e::RIGHT:
      if (rMap[guard.first][guard.second + 1])
        dir = Direction_e::DOWN;
      break;
    case Direction_e::DOWN:
      if (rMap[guard.first + 1][guard.second])
        dir = Direction_e::LEFT;
      break;
    case Direction_e::LEFT:
      if (rMap[guard.first][guard.second - 1])
        dir = Direction_e::UP;
      break;
    }
  }
  path.push_back(guard);
  return path;
}

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  Matrix<bool> map;
  Point_t originalGuard;

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
          originalGuard = MakePoint(map.GetRows() + 1, i);
      }
      map.AddRow(row);
    }
  }

  int obstacles = 0;
  int counter = 0;
  std::vector<Point_t> part1Points = part1(originalGuard, map);

  for (const Point_t& rPoint : part1Points)
  {
    std::cout << "Count: " << counter++ << " of " << part1Points.size() << '\t' << rPoint.first << ' ' << rPoint.second << std::endl;
    if (map[rPoint.first][rPoint.second])
      continue;
    if (rPoint == originalGuard)
      continue;

    Direction_e dir = Direction_e::UP;
    map[rPoint.first][rPoint.second] = true;
    std::vector<std::pair<Point_t, Direction_e>> obsHit;
    Point_t guardCopy = originalGuard;

    // Turn guard
    switch (dir)
    {
    case Direction_e::UP:
      if (map[guardCopy.first - 1][guardCopy.second])
        dir = Direction_e::RIGHT;
      break;
    case Direction_e::RIGHT:
      if (map[guardCopy.first][guardCopy.second + 1])
        dir = Direction_e::DOWN;
      break;
    case Direction_e::DOWN:
      if (map[guardCopy.first + 1][guardCopy.second])
        dir = Direction_e::LEFT;
      break;
    case Direction_e::LEFT:
      if (map[guardCopy.first][guardCopy.second - 1])
        dir = Direction_e::UP;
      break;
    }

    // Move guard
    while (true)
    {
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
    }

    map[rPoint.first][rPoint.second] = false;
  }
  std::cout << "obs: " << obstacles << std::endl;
  return 0;
}
