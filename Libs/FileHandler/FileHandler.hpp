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
    bool GetLineSplit(std::vector<uint32_t>& rLine, const std::string& rSeperator = " ");

    void Close();

    static std::vector<std::string> SplitString(const std::string& rInput, const std::string& rSeperator);

private:
    std::fstream m_file;
};

#endif // FILEHANDLER_HPP_