#ifndef FILEHANDLER_HPP_
#define FILEHANDLER_HPP_

#include <fstream>
#include <vector>

class FileHandler
{
public:
    FileHandler() = default;
    FileHandler(const std::string& rFilePath);

    bool GetLine(std::string& rLine);
    bool IsOpen()const;

    bool GetLineSplit(std::vector<std::string>& rLine, const std::string& rSeperator = " ");

    void Close();

private:
    std::fstream m_file;
};

#endif // FILEHANDLER_HPP_