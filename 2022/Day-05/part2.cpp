#include <iostream>
#include <vector>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    std::vector<std::vector<char>> stacks;

    FileHandler file(filePath);
    if (file.IsOpen())
    {
        // Read the file
        std::string line;
        while (file.GetLine(line))
        {
            if(line.find("move") == std::string::npos) // Stacks
            {
                for(uint index = 0; index < line.size(); ++index)
                {
                    if(line[index] == '[')
                    {
                        std::cout<<"On index: "<<index<<" found character: "<<line[index+1]<<std::endl;
                        uint stackIndex = index / 4;
                        if(stacks.size() <= stackIndex)
                        {
                            stacks.resize(stackIndex+1);
                        }
                        stacks[stackIndex].insert(stacks[stackIndex].begin(), line[index+1]);
                    }
                }
            }
            else
            {
                int first = -1, second = -1, third = -1;
                
                std::vector<std::string> split = file.SplitString(line, " ");

                first = std::stoi(split[1]);
                second = std::stoi(split[3])-1;
                third = std::stoi(split[5])-1;

                std::cout<<first<<" "<<second<<" "<<third<<std::endl;

                std::cout<<"Stacks Before"<<std::endl;
                for(auto i : stacks)
                {
                    for(auto j : i)
                    {
                        std::cout<<j<<"-";
                    }
                    std::cout<<std::endl;
                }
                std::cout<<"--------------"<<std::endl;
                
                for(int i = 0; i < stacks[second].size(); ++i)
                {
                    std::cout<<i<<std::endl;
                    if(i >= stacks[second].size() - first)
                    {
                        std::cout<<"moving "<< stacks[second][i]<<std::endl;
                        stacks[third].push_back(stacks[second][i]);
                    }
                }
                stacks[second].erase(stacks[second].end()-first, stacks[second].end());

                std::cout<<"-----------------"<<std::endl;
                for(auto i : stacks)
                {
                    for(auto j : i)
                    {

                        std::cout<<j<<"-";

                    }
                    std::cout<<std::endl;
                }
                std::cout<<"-------- AFTER ------"<<std::endl;
            }
        }
        for(auto i : stacks)
        {
            std::cout<<i[i.size()-1];
        }
        std::cout<<std::endl;
    }
    return 0;
}