#include <iostream>
#include "FileHandler.hpp"
#include "Map.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";
    FileHandler file(filePath);   

    std::vector<std::string> line;
    uint32_t maxX = 0, maxY = 0;
    std::vector<std::pair<Point, Point>> linesList;
    while(file.GetLineSplit(line, " -> "))
    {
        // Find begin point
        size_t pos = line[0].find(',');
        Point beginPoint;
        beginPoint.x = std::stoi(line[0].substr(0,pos));
        beginPoint.y = std::stoi(line[0].substr(pos+1));

        // Find end point
        pos = line[1].find(',');
        Point endPoint;
        endPoint.x = std::stoi(line[1].substr(0,pos));
        endPoint.y = std::stoi(line[1].substr(pos+1));

        std::pair<Point, Point> linePair(beginPoint, endPoint);
        linesList.push_back(linePair);

        if(endPoint.x > maxX)
            maxX = endPoint.x;
        if(endPoint.y > maxY)
            maxY = endPoint.y;
        if(beginPoint.x > maxX)
            maxX = beginPoint.x;
        if(beginPoint.y > maxY)
            maxY = beginPoint.y;
    }


    Map map(maxX + 1,maxY + 1);

    for(const std::pair<Point, Point>& line : linesList)
    {
        map.AddLine(line.first, line.second, true);
    }
    
    std::cout<<"Number of 2's: "<<map.GetPoints(2).size()<<std::endl;

    file.Close();

    return 0;
}
