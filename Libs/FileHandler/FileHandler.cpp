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