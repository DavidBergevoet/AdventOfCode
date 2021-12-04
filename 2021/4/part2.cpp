#include <iostream>

#include "FileHandler.hpp"
#include "BingoBoard.hpp"

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);

    // Get the input numbers
    std::vector<std::string> numbersStringList;
    std::vector<uint32_t> numbersList;
    file.GetLineSplit(numbersStringList,",");
    for(const std::string& value : numbersStringList)
    {
        numbersList.push_back(std::stoul(value));
    }

    std::vector<Board> bingoBoards;
    Board tempBoard;
    std::vector<std::vector<uint32_t>> tempMatrix;
    std::vector<std::string> line;
    // Get the bingo boards
    while(file.GetLineSplit(line))
    {
        if(line.size() == 0)
        {
            if(tempMatrix.size() > 0)
            {
                tempBoard.SetBoard(tempMatrix);
                bingoBoards.push_back(tempBoard);
            }
            tempBoard = Board();
            tempMatrix.clear();
            continue;
        }
        std::vector<uint32_t> row;
        for(const std::string& value : line)
        {
            row.push_back(std::stoul(value));
        }
        tempMatrix.push_back(row);
    }
    tempBoard.SetBoard(tempMatrix);
    bingoBoards.push_back(tempBoard);


    
    return 0;
}