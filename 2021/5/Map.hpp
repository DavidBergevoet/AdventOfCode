#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <string>
#include <iostream>

struct Point
{
    uint32_t x = 0;
    uint32_t y = 0;
};

class Map
{
public:
    Map(uint32_t maxX, uint32_t maxY);

    void AddLine(Point beginPoint, Point endPoint, bool withDiagonal = false);

    std::vector<Point> GetPoints(uint32_t value)const;

    std::string ToString()const;

private:
    uint32_t m_maxX;
    uint32_t m_maxY;
    std::vector<std::vector<uint32_t>> m_map; // [ROW][COLUMN]
};

#endif // MAP_HPP_
