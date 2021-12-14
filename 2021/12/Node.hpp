#ifndef NODE_HPP_
#define NODE_HPP_

#include <iostream>

class Node // Add a destructor which will remove this node from all adjacent nodes. This will remove the seg fault
{
public:
    bool m_visited;

    Node(const std::string& rNodeSymbol, bool bigNode) 
    : m_symbol(rNodeSymbol)
    , m_bigNode(bigNode)
    , m_visited(false)
    {
    }

    void AddAdjacent(Node* pNode)
    {
        if(!IsAdjacent(pNode))
        {
            m_adjacentNodes.push_back(pNode);
            pNode->AddAdjacent(this);
        }
    }

    const std::string& GetSymbol() const 
    {
        return m_symbol;
    }

    bool GetBigNode() const
    {
        return m_bigNode;
    }

    const std::vector<Node*> GetAdjacent() const
    {
        return m_adjacentNodes;
    }

    bool IsAdjacent(const Node* pNode)
    {
        for(const Node* pCurrentNode : m_adjacentNodes)
        {
            if(pNode == pCurrentNode)
                return true;
        }
        return false;
    }

    std::string ToString() const
    {
        std::stringstream returnString;
        returnString << "Node: "<<m_symbol<<" ("<<m_bigNode<<")"<<"["<<m_visited<<"]\n";
        for(const Node* pNode : m_adjacentNodes)
        {
            returnString << "\t"<<pNode->m_symbol<<"("<<pNode->m_bigNode<<")"<<"["<<m_visited<<"]\n";
        }
        return returnString.str();
    }


private:
    std::vector<Node*> m_adjacentNodes;
    std::string m_symbol;
    bool m_bigNode;
};

#endif // NODE_HPP_