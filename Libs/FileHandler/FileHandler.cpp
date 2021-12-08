#include "FileHandler.hpp"

FileHandler::FileHandler(const std::string& rFilePath): m_file(rFilePath)
{
}

bool FileHandler::GetLine(std::string& rLine)
{
    if(!IsOpen())
        throw std::runtime_error("File is not open!");
    
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
        if(part != "")
            rLine.push_back(part);
    }
    if(line != "")
        rLine.push_back(line);
    return true;
}

bool FileHandler::GetLineSplit(std::vector<uint32_t>& rLine, const std::string& rSeperator /*= " "*/)
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
        if(part != "")
            rLine.push_back(std::stoul(part));
    }
    if(line != "")
        rLine.push_back(std::stoul(line));
    return true;
}

std::vector<std::string> FileHandler::SplitString(const std::string& rInput, const std::string& rSeperator)
{
    std::vector<std::string> returnVector;
    size_t pos = 0;
    std::string part, inputCopy = rInput;
    while((pos = inputCopy.find(rSeperator)) != std::string::npos)
    {
        part = inputCopy.substr(0, pos);
        inputCopy.erase(0, pos + rSeperator.length());
        returnVector.push_back(part);
    }
    if(inputCopy != "")
        returnVector.push_back(inputCopy);
    
    return returnVector;
}