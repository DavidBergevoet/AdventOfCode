#include <iostream>
#include "FileHandler.hpp"
#include "Matrix.hpp"

class Node
{
public:
    Node()
    : m_weight(0)
    , m_reachedSteps(UINT32_MAX)
    , m_visited(false)
    {}
    Node(uint32_t weight)
    : m_weight(weight)
    , m_reachedSteps(UINT32_MAX)
    , m_visited(false)
    {}

    uint32_t m_weight;
    uint32_t m_reachedSteps;
    bool m_visited;
};

std::ostream& operator<<(std::ostream& os, const Node& rNode) 
    {
        std::string reachedString;
        if(rNode.m_reachedSteps < 10)
            reachedString += "0";
        if(rNode.m_reachedSteps != UINT32_MAX)
            reachedString += std::to_string(rNode.m_reachedSteps);
        else
            reachedString += "-1";
        if(rNode.m_visited)
        {
            os << "*"<<rNode.m_weight<<"("<<reachedString<<")*";
        }
        else
        {
            os << " "<<rNode.m_weight<<"("<<reachedString<<") ";
        }
        return os;
    }

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");

    Matrix<Node> field;
    std::string line;
    while(file.GetLine(line))
    {
        std::vector<Node> nodeLine;
        for(char c : line)
            nodeLine.push_back(Node(c-'0'));

        field.SetColumns(line.size());
        field.AddRow(nodeLine);
    }

    // std::cout<<field<<std::endl;

    std::vector<Point_t> indices { Point_t(0, 0) };
    field[0][0].m_reachedSteps = 0;
    field[0][0].m_visited = true;
    std::vector<Point_t> diagonal;

    uint32_t currentX = 1;
    uint32_t currentY = 0;
    while(currentY < field.GetRows())
    {
        diagonal = field.GetDiagonalPoints(Point_t(currentY, currentX), true, false);
        for(const Point_t& point : diagonal)
        {
            field[point.first][point.second].m_visited = true;
            std::vector<Point_t> adjacents = field.GetAdjacentPoints(point, false);
            for(const Point_t& adjacent : adjacents)
            {
                if(field[adjacent.first][adjacent.second].m_visited)
                {
                    if(field[point.first][point.second].m_reachedSteps > 
                        field[adjacent.first][adjacent.second].m_reachedSteps + field[point.first][point.second].m_weight)
                    {
                        field[point.first][point.second].m_reachedSteps = field[adjacent.first][adjacent.second].m_reachedSteps + field[point.first][point.second].m_weight;
                    }
                }
            }
        }
        if(currentX < field.GetColumns()-1)
            currentX++;
        else
            currentY++;
    }

    // std::cout<<field<<std::endl;

    std::cout<<"Min steps: "<<field[field.GetRows()-1][field.GetColumns()-1].m_reachedSteps<<std::endl;

    return 0;
}
