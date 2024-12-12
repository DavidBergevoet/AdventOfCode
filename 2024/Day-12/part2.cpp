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

void GetAreaPerimeterOfPoint(const Point_t& rPoint, std::vector<Point_t>& rPlot)
{
  if (!garden[rPoint].visited)
  {
    rPlot.push_back(rPoint);

    garden[rPoint].visited = true;
    const auto adjacentPoints = garden.GetAdjacentPoints(rPoint, false);

    for (const Point_t& rAdjPoint : adjacentPoints)
    {
      if (garden[rAdjPoint].character == garden[rPoint].character && !garden[rAdjPoint].visited)
      {
        GetAreaPerimeterOfPoint(rAdjPoint, rPlot);
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

  std::vector<std::vector<Point_t>> plots;

  for (const Point_t& rPoint : garden.GetAllPoints())
  {
    if (!garden[rPoint].visited)
    {
      std::vector<Point_t> plot;
      GetAreaPerimeterOfPoint(rPoint, plot);
      plots.push_back(plot);
    }
  }

  for (const std::vector<Point_t>& rPlot : plots)
  {
    uint plotCorners = 0;
    for (const Point_t& rPoint : rPlot)
    {
      const auto adjPoints = garden.GetAdjacentPoints(rPoint, false);
      const auto diagPoints = garden.GetAdjacentDiagonalPoints(rPoint);
      uint counter = 0;
      bool hasTop = false, hasBottom = false, hasRight = false, hasLeft = false;
      bool hasTopLeft = false, hasTopRight = false, hasBottomRight = false, hasBottomLeft = false;

      for (const Point_t& rDiagPoint : diagPoints)
      {
        if (garden[rDiagPoint].character == garden[rPoint].character)
        {
          if (rDiagPoint.first == rPoint.first - 1 && rDiagPoint.second == rPoint.second - 1)
            hasTopLeft = true;
          if (rDiagPoint.first == rPoint.first + 1 && rDiagPoint.second == rPoint.second + 1)
            hasBottomRight = true;
          if (rDiagPoint.first == rPoint.first - 1 && rDiagPoint.second == rPoint.second + 1)
            hasTopRight = true;
          if (rDiagPoint.first == rPoint.first + 1 && rDiagPoint.second == rPoint.second - 1)
            hasBottomLeft = true;
        }
      }
      for (const Point_t& rAdjPoint : adjPoints)
      {
        if (garden[rAdjPoint].character == garden[rPoint].character)
        {
          if (rAdjPoint.first == rPoint.first - 1)
            hasTop = true;
          if (rAdjPoint.first == rPoint.first + 1)
            hasBottom = true;
          if (rAdjPoint.second == rPoint.second + 1)
            hasRight = true;
          if (rAdjPoint.second == rPoint.second - 1)
            hasLeft = true;
        }
      }
      if (!hasTop && !hasRight)
        plotCorners++;
      if (!hasRight && !hasBottom)
        plotCorners++;
      if (!hasBottom && !hasLeft)
        plotCorners++;
      if (!hasLeft && !hasTop)
        plotCorners++;

      if (hasTop && hasLeft && !hasTopLeft)
        plotCorners++;
      if (hasTop && hasRight && !hasTopRight)
        plotCorners++;
      if (hasBottom && hasLeft && !hasBottomLeft)
        plotCorners++;
      if (hasBottom && hasRight && !hasBottomRight)
        plotCorners++;
    }

    // std::cout << "PlotCorners: " << garden[rPlot[0]].character << " " << plotCorners << std::endl;
    total += plotCorners * rPlot.size();
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}
