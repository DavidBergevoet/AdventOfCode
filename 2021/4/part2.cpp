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

    std::cout<<"Total bingo boards: "<<bingoBoards.size()<<std::endl;


    // Check bingo boards
    std::vector<uint32_t> returnValues;
    bool lastBingoBoardBingo = false;
    for(uint32_t value : numbersList)
    {
        for(size_t i = 0; i < bingoBoards.size(); ++i)
        {
            bingoBoards[i].MarkValue(value);
            if(bingoBoards[i].CheckBingo(returnValues))
            {
                if(bingoBoards.size() == 1)
                {
                    std::cout<<"Last bingo board has bingo!"<<std::endl;
                    lastBingoBoardBingo = true;
                }
                else
                {
                    bingoBoards.erase(bingoBoards.begin() + i);
                    --i;
                }
            }
        }
        if(lastBingoBoardBingo)
            break;
    }

    std::cout<<"Bingo boards size: "<<bingoBoards.size()<<std::endl;

    std::vector<uint32_t> unmarkedNumbers = bingoBoards[0].GetUnmarkedNumbers();
    uint32_t unmarkedNumbersSum = 0;
    for(uint32_t value : unmarkedNumbers)
    {
        unmarkedNumbersSum += value;
    }

    std::vector<uint32_t> markedNumbers = bingoBoards[0].GetMarkedValues();
    uint32_t lastMarkedNumber = markedNumbers[markedNumbers.size() - 1];
    std::cout<<"Last marked number: "<<lastMarkedNumber<<std::endl;
    std::cout<<"Unmarked numbers sum: "<<unmarkedNumbersSum<<std::endl;
    std::cout<<"Multiplied: "<<unmarkedNumbersSum * lastMarkedNumber<<std::endl;
    
    return 0;
}