#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"


class Node {
public:
    Node(uint weight = 0):m_height(weight),m_steps(UINT32_MAX){}

    int m_height;
    uint32_t m_steps;
};
std::ostream& operator<<(std::ostream& rOs, const Node& rNode)
{
    if(rNode.m_height < 10)
        rOs << '0';
    rOs << rNode.m_height;
    if(rNode.m_steps != UINT32_MAX)
        rOs << '|' << rNode.m_steps;
    return rOs;
}

Matrix<Node> map;

void CheckAdjacent(const Point_t& rPoint, uint32_t numberOfSteps, std::vector<Point_t> checked)
{
    if(numberOfSteps < map[rPoint].m_steps)
        map[rPoint].m_steps = numberOfSteps;

    checked.push_back(rPoint);

    std::vector<Point_t> adjacent = map.GetAdjacentPoints(rPoint, false);

    for(const Point_t& rAdj : adjacent)
    {
        bool inChecked = false;
        for(const Point_t& rCheck : checked)
        {
            if(rCheck == rAdj)
            {
                inChecked = true;
                break;
            }
        }

        if(!inChecked && std::abs(map[rAdj].m_height - map[rPoint].m_height) <= 1) // If the height difference is <= 1
        {
            CheckAdjacent(rAdj, numberOfSteps+1, checked);
        }
    }
}

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);

    Point_t startPoint;
    Point_t endPoint;

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
                    row.push_back(Node('z'-'a'));
                }
                else
                {
                    row.push_back(Node(line[i] - 'a'));
                }
            }
            map.AddRow(row);
        }
    }

    CheckAdjacent(startPoint,0,std::vector<Point_t>());

    std::cout<<map<<std::endl;


    std::cout<<"Endpoint: "<<map[endPoint].m_steps<<std::endl;
    return 0;
}