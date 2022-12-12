#include <iostream>
#include <queue>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"


class Node {
public:
    Node(uint weight = 0, uint32_t steps = UINT32_MAX):m_height(weight),m_steps(steps),m_visited(false){}

    int m_height;
    uint32_t m_steps;

    bool m_visited;
    Point_t m_previousPoint;
};
std::ostream& operator<<(std::ostream& rOs, const Node& rNode)
{
    if(rNode.m_height < 10)
        rOs << '0';
    rOs << rNode.m_height;
    if(rNode.m_steps != UINT32_MAX)
        rOs << '|' <<((rNode.m_steps < 10) ? "0" : "") << rNode.m_steps;
    else
        rOs <<"|--";
    // rOs<<(rNode.m_visited) ? 1 : 0;
    return rOs;
}

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);

    Point_t startPoint;
    Point_t endPoint;

    Matrix<Node> map;

    if (file.IsOpen())
    {
        // Read the file
        std::string line;
        while(file.GetLine(line))
        {
            if(map.GetColumns() != line.size())
                map.Resize(0, line.size());

            std::vector<Node> row;
            for(size_t i = 0; i < line.size(); ++i)
            {
                if(line[i] == 'S')
                {
                    startPoint = std::make_pair<int64_t, int64_t>(map.GetRows(), i);
                    row.push_back(Node(0));
                }
                else if(line[i] == 'E')
                {
                    endPoint = std::make_pair<int64_t, int64_t>(map.GetRows(), i);
                    row.push_back(Node('z'-'a', 0));
                }
                else
                {
                    row.push_back(Node(line[i] - 'a'));
                }
            }
            map.AddRow(row);
        }
    }

    std::queue<Point_t> queue;
    queue.push(endPoint);

    while(queue.size() > 0)
    {
        Point_t firstPoint=queue.front();
        queue.pop();

        std::vector<Point_t> adjacent = map.GetAdjacentPoints(firstPoint, false);
        for(const Point_t& rAdj : adjacent)
        {
            uint32_t newStep = map[firstPoint].m_steps + 1;
            if(map[rAdj].m_height - map[firstPoint].m_height >= -1)
            {
                if(map[rAdj].m_steps > newStep)
                {
                    map[rAdj].m_steps = newStep;
                    queue.push(rAdj);
                }
            }
        }
    }

    std::cout<<map<<std::endl;

    uint32_t lowestSteps = UINT32_MAX;

    for(size_t row = 0; row < map.GetRows(); ++row)
    {
        for(size_t col = 0; col < map.GetColumns(); ++col)
        {
            if(map[row][col].m_height == 0 && map[row][col].m_steps < lowestSteps)
            {
                lowestSteps = map[row][col].m_steps;
            }
        }
    }

    std::cout<<"Lowest: "<< lowestSteps<<std::endl;
    return 0;
}