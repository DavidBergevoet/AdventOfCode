#include "FileHandler.hpp"

FileHandler::FileHandler(const std::string& rFilePath): m_file(rFilePath)
{
}

bool FileHandler::GetLine(std::string& rLine)
{
    if(!IsOpen())
        return false;
    
    return std::getline(m_file, rLine) ? true : false;
}

bool FileHandler::IsOpen() const
{
    return m_file.is_open();
}

void FileHandler::Close()
{
    if(IsOpen())
        m_file.close();
}

bool FileHandler::GetLineSplit(std::vector<std::string>& rLine, const std::string& rSeperator /*= " "*/)
{
    std::string line;
    rLine.clear();
    if(!GetLine(line))
        return false;

    size_t position = 0;
    std::string part;
    while((position = line.find(rSeperator)) != std::string::npos)
    {
        part = line.substr(0, position);
        line.erase(0, position + rSeperator.length());
        rLine.push_back(part);
    }
    rLine.push_back(line);
}