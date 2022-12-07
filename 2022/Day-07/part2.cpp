#include <iostream>
#include <vector>

#include "FileHandler.hpp"


class File{
    public:
    File(const std::string& rName = "",uint size = 0):m_name(rName),m_size(size){}

    std::string m_name;
    uint m_size;
};

class Directory{
    public:
    Directory(const std::string& rName = ""):m_name(rName),m_pParent(nullptr){}

    std::string m_name;
    Directory* m_pParent;
    std::vector<Directory*> m_childDirectories;
    std::vector<File> m_files;

    uint64_t GetSize()const
    {
        uint64_t returnSize=0;
        for(const File& rFile: m_files)
        {
            returnSize+=rFile.m_size;
        }
        for(const Directory* pDir: m_childDirectories)
        {
            returnSize += pDir->GetSize();
        }
        return returnSize;
    }
};

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    uint64_t characterIndex = 0;

    std::vector<Directory> directories(512);
    uint64_t dirIndex = 0;

    FileHandler file(filePath);

    Directory* currentDirectory = nullptr;

    if (file.IsOpen())
    {
        // Read the file
        std::string line;
        while(file.GetLine(line) && line.size() > 0)
        {
            if(line[0] == '$')
            {
                std::vector<std::string> split = file.SplitString(line, " ");
                if(split[1] == "cd")
                {
                    if(currentDirectory == nullptr)
                    {
                        directories[dirIndex] = (Directory(split[2]));
                        currentDirectory = &directories[dirIndex];
                        dirIndex++;
                    }
                    else if(split[2] != "..")
                    {
                        for(size_t i = 0; i < currentDirectory->m_childDirectories.size(); ++i)
                        {
                            if(currentDirectory->m_childDirectories[i]->m_name == split[2])
                            {
                                currentDirectory = currentDirectory->m_childDirectories[i];
                            }
                        }
                    }
                    else // cd ..
                    {
                        currentDirectory = currentDirectory->m_pParent;
                    }
                }
            }
            else // LS response
            {
                std::vector<std::string> split = file.SplitString(line, " ");
                if(split[0] == "dir")
                {
                    Directory tempDir = Directory(split[1]);
                    tempDir.m_pParent = currentDirectory;
                    directories[dirIndex] = tempDir;
                    currentDirectory->m_childDirectories.push_back(&directories[dirIndex]);
                    dirIndex++;
                }
                else // File
                {
                    File tempFile = File(split[1], std::stoul(split[0]));
                    currentDirectory->m_files.push_back(tempFile);
                }
            }
        }
    }

    uint64_t leastAmountOfSpace = UINT64_MAX;
    uint64_t unused = 70000000 - directories[0].GetSize();
    uint64_t amountNeeded = 30000000 - unused;
    for(size_t i = 0;i<dirIndex;++i)
    {
        if(directories[i].GetSize() > amountNeeded && directories[i].GetSize() < leastAmountOfSpace)
        {
            leastAmountOfSpace = directories[i].GetSize();
        }
    }
    std::cout<<"Least amount of space: "<<leastAmountOfSpace<<std::endl;
    return 0;
}