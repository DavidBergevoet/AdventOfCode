#include <iostream>
#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");
    const std::string openingChars = "([{<";

    std::string line;
    uint32_t score=0;

    while(file.GetLine(line))
    {
        std::vector<char> levels;
        bool illegal = false;

        for(char character : line)
        {
            if(illegal)
                break;
            // std::cout<<"Char: "<<character<<std::endl;
            if(openingChars.find(character) != std::string::npos)
            {
                // std::cout<<"New Level!"<<std::endl;
                levels.push_back(character);
            }
            else
            {
                switch(character)
                {
                    case ')':
                    {
                        if(levels[levels.size()-1] != '(')
                        {
                            // std::cout<<"Illegal char found"<<std::endl;
                            illegal = true;
                            score += 3;
                        }
                        break;
                    }
                    case ']':
                    {
                        if(levels[levels.size()-1] != '[')
                        {
                            // std::cout<<"Illegal char found"<<std::endl;
                            illegal = true;
                            score += 57;
                        }
                        break;
                    }
                    case '}':
                    {
                        if(levels[levels.size()-1] != '{')
                        {
                            // std::cout<<"Illegal char found"<<std::endl;
                            illegal = true;
                            score += 1197;
                        }
                        break;
                    }
                    case '>':
                    {
                        if(levels[levels.size()-1] != '<')
                        {
                            // std::cout<<"Illegal char found"<<std::endl;
                            illegal = true;
                            score += 25137;
                        }
                        break;
                    }
                }
                if(!illegal)
                    levels.erase(levels.end()-1);
            }
        }
    }

    std::cout<<"Score: "<<score<<std::endl;
    return 0;
}
