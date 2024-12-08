#include <iostream>
#include <map>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

int main(int argc, char const* argv[])
{
  std::string filePath = "input.txt";

  FileHandler file(filePath);

  uint width = 0, height = 0;
  std::map<char, std::vector<Point_t>> antennas;
  if (file.IsOpen())
  {
    // Read the file
    std::string line;
    while (file.GetLine(line))
    {
      if (line.size() != width)
        width = line.size();

      for (int i = 0; i < line.size(); ++i)
      {
        if (line[i] != '.')
        {
          antennas[line[i]].push_back(MakePoint(height, i));
        }
      }
      height++;
    }
  }

  Matrix<char> visualMap(height, width);
  visualMap.Fill('.');

  std::vector<Point_t> antiNodes;
  for (const auto& rAntenna : antennas)
  {
    for (int i = 0; i < rAntenna.second.size(); ++i)
    {
      visualMap[rAntenna.second[i]] = rAntenna.first;
      for (int j = 0; j < rAntenna.second.size(); ++j)
      {
        if (i != j)
        {
          visualMap[rAntenna.second[j]] = rAntenna.first;

          int colDiff = rAntenna.second[i].second - rAntenna.second[j].second;
          int rowDiff = rAntenna.second[i].first - rAntenna.second[j].first;

          Point_t antiNode = MakePoint(rAntenna.second[i].first + rowDiff, rAntenna.second[i].second + colDiff);
          if (antiNode.first >= 0 && antiNode.first < height && antiNode.second >= 0 && antiNode.second < width)
          {
            bool contains = false;
            for (const auto& rPoint : antiNodes)
            {
              if (rPoint == antiNode)
              {
                contains = true;
                break;
              }
            }
            if (!contains)
              antiNodes.push_back(antiNode);
          }
        }
      }
    }
  }

  // for (const auto& rAntenna : antennas)
  // {
  //   std::cout << "Antenna: " << rAntenna.first << " - ";
  //   for (const auto& rPoint : rAntenna.second)
  //     std::cout << "(" << rPoint.first << ',' << rPoint.second << "),";
  //   std::cout << std::endl;
  // }

  // std::cout << visualMap.ToCleanString() << std::endl;

  std::cout << "AntiNodes (" << antiNodes.size() << "): ";
  // for (const auto& rPoint : antiNodes)
  // {
  //   visualMap[rPoint] = '#';
  //   std::cout << "(" << rPoint.first << ',' << rPoint.second << "),";
  // }
  // std::cout << std::endl;

  // std::cout << visualMap.ToCleanString() << std::endl;

  return 0;
}
