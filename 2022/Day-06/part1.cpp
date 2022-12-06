#include <iostream>
#include <vector>

#include "FileHandler.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    uint64_t characterIndex = 0;

    std::vector<char> lastCharacters{0, 0, 0, 0};

    FileHandler file(filePath);
    if (file.IsOpen())
    {
        // Read the file
        std::string line;
        file.GetLine(line);

        for (uint64_t i = 0; i < line.size(); ++i)
        {
            uint index = i % 4;
            lastCharacters[index] = line[i];

            bool different = true;
            for (uint c = 0; c < lastCharacters.size(); ++c)
            {
                if (lastCharacters[c] == 0)
                {
                    different = false;
                    break;
                }
                for (uint oc = 0; oc < lastCharacters.size(); ++oc)
                {
                    if (oc != c)
                    {
                        if (lastCharacters[oc] == lastCharacters[c])
                        {
                            different = false;
                            break;
                        }
                    }
                }
            }
            if(different)
            {
                std::cout<<"Diff on character: "<<i+1<<std::endl;
                return 0;
            }
        }
    }
    return 1;
}