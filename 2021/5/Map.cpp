#include "Map.hpp"
#include <sstream>

Map::Map(uint32_t maxX, uint32_t maxY) : m_maxX(maxX), m_maxY(maxY)
{
    m_map.Resize(maxY, maxX);
}

void Map::AddLine(Point beginPoint, Point endPoint, bool withDiagonal)
{

    if (beginPoint.x >= m_maxX || beginPoint.y >= m_maxY)
        throw std::invalid_argument("Beginpoint is out of range!");
    if(endPoint.x >= m_maxX || endPoint.y >= m_maxY)
        throw std::invalid_argument("Endpoint is out of range!");

    int dX =  endPoint.x - beginPoint.x;
    int dY = endPoint.y - beginPoint.y;

    if(dX == 0 && dY > 0) // Line is Vertical
    {
        for(size_t i = 0; i <= abs(dY); ++i)
        {
            if(endPoint.y > beginPoint.y)
            {
                m_map[beginPoint.y + i][beginPoint.x] += 1;
            }
            else
            {
                m_map[endPoint.y + i][beginPoint.x] += 1;
            }
        }
    }
    else if(dX == 0 && dY < 0)
    {
        for(size_t i = 0; i <= abs(dY); ++i)
        {
            if(endPoint.y > beginPoint.y)
            {
                m_map[endPoint.y - i][beginPoint.x] += 1;
            }
            else
            {
                m_map[beginPoint.y - i][beginPoint.x] += 1;
            }
        }
    }
    else if(dY == 0 && dX > 0)
    {
        for(size_t i = 0; i <= abs(dX); ++i)
        {
            if(endPoint.x > beginPoint.x)
            {
                m_map[beginPoint.y][beginPoint.x + i] += 1;
            }
            else
            {
                m_map[beginPoint.y][endPoint.x + i] += 1;
            }
        }
    }
    else if(dY == 0 && dX < 0)
    {
        for(size_t i = 0; i <= abs(dX); ++i)
        {
            if(endPoint.x > beginPoint.x)
            {
                m_map[beginPoint.y][endPoint.x - i] += 1;
            }
            else
            {
                m_map[beginPoint.y][beginPoint.x - i] += 1;
            }
        }
    }
    else if(withDiagonal && abs(dX) == abs(dY))
    {
        if((dX > 0 && dY < 0) || (dX < 0 && dY > 0))
        {
            for(size_t i = 0; i <= abs(dX); ++i)
            {
                if(endPoint.x > beginPoint.x)
                {
                    m_map[beginPoint.y - i][beginPoint.x + i] += 1;
                }
                else
                {
                     m_map[endPoint.y - i][endPoint.x + i] += 1;
                }
            }
        }
        if((dX > 0 && dY > 0) || (dX < 0 && dY < 0))
        {
            for(size_t i = 0; i <= abs(dX); ++i)
            {
                if(endPoint.x > beginPoint.x)
                {
                    m_map[beginPoint.y + i][beginPoint.x + i] += 1;
                }
                else
                {
                    m_map[endPoint.y + i][endPoint.x + i] += 1;
                }
            }
        }
    }
}

std::vector<Point> Map::GetPoints(uint32_t value) const
{
    std::vector<Point> returnVector;

    for(size_t i = 0; i < m_maxY; ++i)
    {
        for(size_t j = 0; j < m_maxX; ++j)
        {
            if(m_map[i][j] >= value)
            {
                Point point;
                point.x = j;
                point.y = i;
                returnVector.push_back(point);
            }
        }
    }
    return returnVector;
}

std::string Map::ToString() const
{
    return m_map.ToString();
}