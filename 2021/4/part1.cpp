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

    // Mark the bingo values and check bingo
    std::vector<uint32_t> returnValues;
    bool foundBingo = false;
    uint32_t bingoBoardIndex = 0;
    for(uint32_t value : numbersList)
    {
        for(size_t i = 0; i < bingoBoards.size(); ++i)
        {
            bingoBoards[i].MarkValue(value);
            if(bingoBoards[i].CheckBingo(returnValues))
            {
                std::cout<<"Bingo at index: "<<i<<std::endl;
                bingoBoardIndex = i;
                foundBingo = true;
                break;
            }
        }
        if(foundBingo)
            break;
    }

    // Print the bingo values
    for(uint32_t value : returnValues)
    {
        std::cout<<"\t"<<value<<std::endl;
    }

    // Get the unmarked numbers
    std::vector<uint32_t> unmarked = bingoBoards[bingoBoardIndex].GetUnmarkedNumbers();

    uint32_t unmarkedSum = 0;
    for(uint32_t value : unmarked)
    {
        unmarkedSum += value;
    }

    std::cout<<"Sum of unmarked: "<<unmarkedSum<<std::endl;
    std::vector<uint32_t> markedValues = bingoBoards[bingoBoardIndex].GetMarkedValues();
    std::cout<<"Last called: "<<markedValues[markedValues.size()-1]<<std::endl;

    std::cout<<"Multiplied: "<<unmarkedSum * markedValues[markedValues.size()-1]<<std::endl;

    return 0;
}