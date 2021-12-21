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

    std::vector<Point_t> indices{std::pair<uint32_t,uint32_t>(0,0)};
    field[0][0].m_reachedSteps=0;
    std::vector<Point_t> newIndices;

    uint32_t count = 0;

    while(indices.size() != 0)
    {
        std::cout<<count++<<std::endl;
        for(const auto& index : indices)
        {
            field[index.first][index.second].m_visited = true;
            std::vector<Point_t> adjacent = field.GetAdjacentPoints(index, false);
            for(const auto& point : adjacent)
            {
                if(field[point.first][point.second].m_reachedSteps > 
                    field[index.first][index.second].m_reachedSteps + field[point.first][point.second].m_weight)
                {
                    field[point.first][point.second].m_reachedSteps = field[index.first][index.second].m_reachedSteps + field[point.first][point.second].m_weight;
                }
                if(!field[point.first][point.second].m_visited)
                {
                    newIndices.push_back(point);
                }
            }        
        }

        // std::cout<<"NEW: "<<newIndices.size()<<std::endl;
        // for(const auto& point : newIndices)
        // {
        //     std::cout<<point.first<<":"<<point.second<<std::endl;
        // }
        indices = newIndices;
        newIndices.clear();
    }
    
    std::cout<<field<<std::endl;

    std::cout<<"Min steps: "<<field[field.GetRows()-1][field.GetColumns()-1].m_reachedSteps<<std::endl;

    return 0;
}
