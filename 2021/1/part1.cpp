#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";
    std::vector<uint32_t> fileInputVector;

    std::ifstream file(filePath);
    if(file.is_open())
    {
        // Read the file
        std::string line;
        while(std::getline(file, line))
        {
            fileInputVector.push_back(std::stoul(line));
        }

        // Get the number of increases
        uint32_t increasedNumbers = 0;
        for(size_t i = 1; i<fileInputVector.size(); ++i)
        {
            if(fileInputVector[i-1] < fileInputVector[i])
            {
                increasedNumbers++;
            }
        }
        std::cout<<"Total: "<<increasedNumbers<<std::endl;
    }
    else
    {
        std::cerr<<"File cannot be opened"<<std::endl;
        return 1;
    }
    file.close();
    return 0;
}
