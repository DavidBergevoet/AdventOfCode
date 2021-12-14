#include <iostream>
#include <sstream>
#include "FileHandler.hpp"
#include "Node.hpp"

std::vector<Node> graph;

void ResetVisited()
{
    for(Node& rNode : graph)
    {
        rNode.m_visited = false;
    }
}

bool IsInPath(const Node& rNode, const std::vector<Node>& rPath)
{
    for(const Node& rPathNode : rPath)
    {
        if(rPathNode.GetSymbol() == rNode.GetSymbol())
            return true;
    }
    return false;
}

void FindPathInternal(Node* pNode, Node* pEndNode, const std::vector<Node>& rPath, std::vector<std::vector<Node>>& rTotalPaths)
{
    std::vector<Node> pathCopy = rPath;
    if(pNode == pEndNode)
    {
        pathCopy.push_back(*pNode);
        rTotalPaths.push_back(pathCopy);
        return;
    }
    else if(!pNode->GetBigNode() && IsInPath(*pNode, pathCopy))
        return;
    pathCopy.push_back(*pNode);

    for(Node* pAdjacent : pNode->GetAdjacent())
    {
        FindPathInternal(pAdjacent,pEndNode, pathCopy, rTotalPaths);
    }
}

std::vector<std::vector<Node>> FindPaths()
{
    std::vector<std::vector<Node>> totalPaths;
    std::vector<Node> path;

    FindPathInternal(&graph[0], &graph[graph.size()-1], path, totalPaths);


    // print the path
    std::cout<<"Paths: "<<totalPaths.size()<<std::endl;
    for(const std::vector<Node>& rPath : totalPaths)
    {
        std::cout<<"\tPath: "<<rPath.size()<<std::endl<<"\t\t";
        for(const Node& rNode : rPath)
        {
            std::cout<<rNode.GetSymbol()<<" ";
        }
        std::cout<<"\n";
    }
}

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");

    std::vector<std::string> line;
    std::vector<std::pair<std::string, std::string>> relations;

    // Get the distinct nodes and all relations
    while(file.GetLineSplit(line,"-"))
    {
        relations.push_back(std::pair<std::string, std::string>(line[0], line[1]));
        bool firstInGraph = false, 
            secondInGraph = false;

        for(Node& rNode : graph)
        {
            if(rNode.GetSymbol() == line[0])
                firstInGraph = true;
            if(rNode.GetSymbol() == line[1])
                secondInGraph = true; 
        }
        if(!firstInGraph)
            graph.push_back(Node(line[0], line[0][0] < 97));
        if(!secondInGraph)
            graph.push_back(Node(line[1], line[1][0] < 97));
    }

    // Add the relations to the graph
    for(const auto& rRelation : relations)
    {
        Node* firstNode = nullptr;
        Node* secondNode = nullptr;

        for(Node& rNode : graph)
        {
            if(rNode.GetSymbol() == rRelation.first)
                firstNode = &rNode;
            else if(rNode.GetSymbol() == rRelation.second)
                secondNode= &rNode;
        }

        if(firstNode == nullptr)
            return -1;
        if(secondNode == nullptr)
            return -2;
        firstNode->AddAdjacent(secondNode);
    }

    // Print the graph
    std::cout<<"Nodes"<<std::endl;
    for(const Node& rNode : graph)
    {
        std::cout<<rNode.ToString();
    }

    FindPaths();
    
    return 0;
}
