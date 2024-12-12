#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

typedef struct
{
  char character;
  bool visited;
} Plot_t;

std::ostream& operator<<(std::ostream& rOs, const Plot_t& rPlot)
{
  return rOs << rPlot.character << '(' << rPlot.visited << ')';
}

Matrix<Plot_t> garden;

void GetAreaPerimeterOfPoint(const Point_t& rPoint, std::pair<uint, uint>& rAreaPerimeterPair)
{
  if (!garden[rPoint].visited)
  {
    rAreaPerimeterPair.first++;
    garden[rPoint].visited = true;
    const auto adjacentPoints = garden.GetAdjacentPoints(rPoint, false);
    const auto diagonalPoints = garden.GetAdjacentDiagonalPoints(rPoint);

    for (const Point_t& rAdjPoint : adjacentPoints)
    {
      if (garden[rAdjPoint].character != garden[rPoint].character)
      {
        rAreaPerimeterPair.second++;
      }
      else if (!garden[rAdjPoint].visited)
      {
        GetAreaPerimeterOfPoint(rAdjPoint, rAreaPerimeterPair);
      }
    }
  }
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
      std::vector<Plot_t> plotLine;
      for (char c : line)
      {
        plotLine.push_back(Plot_t{c, false});
      }
      if (plotLine.size() != garden.GetColumns())
        garden.Resize(0, plotLine.size());
      garden.AddRow(plotLine);
    }
  }

  uint64_t total = 0;

  for (const Point_t& rPoint : garden.GetAllPoints())
  {
    if (!garden[rPoint].visited)
    {
      std::pair<uint, uint> areaPerimeterPair;
      GetAreaPerimeterOfPoint(rPoint, areaPerimeterPair);
      total += areaPerimeterPair.first * areaPerimeterPair.second;
      // std::cout << garden[rPoint].character << " " << areaPerimeterPair.first << ' ' << areaPerimeterPair.second << std::endl;
    }
  }

  // std::cout << garden << std::endl;

  std::cout << "Total: " << total << std::endl;

  return 0;
}
