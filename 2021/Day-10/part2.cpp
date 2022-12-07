#include <iostream>
#include <algorithm>
#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    FileHandler file("input.txt");
    const std::string openingChars = "([{<";

    std::string line;
    std::vector<uint64_t> scores;

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
                            illegal = true;
                        }
                        break;
                    }
                    case ']':
                    {
                        if(levels[levels.size()-1] != '[')
                        {
                            illegal = true;
                        }
                        break;
                    }
                    case '}':
                    {
                        if(levels[levels.size()-1] != '{')
                        {
                            illegal = true;
                        }
                        break;
                    }
                    case '>':
                    {
                        if(levels[levels.size()-1] != '<')
                        {
                            illegal = true;
                        }
                        break;
                    }
                }
                if(!illegal)
                    levels.erase(levels.end()-1);
            }
        }
        // Check for unfinished lines
        if(!illegal)
        {
            uint64_t score = 0;
            for(int64_t i = levels.size()-1;i >= 0; --i)
            {
                switch(levels[i])
                {
                    case '(':
                    {
                        score = (score * 5) + 1;
                        break;
                    }
                    case '[':
                    {
                        score = (score * 5) + 2;
                        break;
                    }
                    case '{':
                    {
                        score = (score * 5) + 3;
                        break;
                    }
                    case '<':
                    {
                        score = (score * 5) + 4;
                        break;
                    }
                }
            }
            scores.push_back(score);
        }
    }

    std::sort(scores.begin(), scores.end());

    std::cout<<"Scores!"<<std::endl;
    for(uint64_t score : scores)
        std::cout<<"\t"<<score<<std::endl;

    std::cout<<"Middle score: "<<scores.at(scores.size() / 2)<<std::endl;
    return 0;
}
