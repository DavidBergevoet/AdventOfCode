#ifndef FILEHANDLER_HPP_
#define FILEHANDLER_HPP_

#include <fstream>

class FileHandler
{
public:
    FileHandler() = default;
    FileHandler(const std::string& rFilePath);

    bool GetLine(std::string& rLine);
    bool IsOpen()const;

    void Close();

private:
    std::fstream m_file;
};

#endif // FILEHANDLER_HPP_