#include <iostream>
#include <vector>

class Board
{
public:
    Board() = default;

    void SetBoard(std::vector<std::vector<uint32_t>> board)
    {
        m_matrix = board;
    }
    void MarkValue(uint32_t value)
    {
        m_markedValues.push_back(value);
    }

    std::vector<uint32_t> GetMarkedValues()const
    {
        return m_markedValues;
    }

    std::vector<uint32_t> GetUnmarkedNumbers()const
    {
        std::vector<uint32_t> returnValues;
        for(const std::vector<uint32_t>& row : m_matrix)
        {
            for(uint32_t columnValue : row)
            {
                bool isMarked = false;
                for(uint32_t markedValue : m_markedValues)
                {
                    if(columnValue == markedValue)
                    {
                        isMarked = true;
                    }
                }
                if(!isMarked)
                {
                    returnValues.push_back(columnValue);
                }
            }
        }
        return returnValues;
    }

    bool CheckBingo(std::vector<uint32_t>& rBingoValues)
    {
        if(CheckHorizontal(rBingoValues))
            return true;
        if(CheckVertical(rBingoValues))
            return true;
        return false;
    }

    bool CheckHorizontal(std::vector<uint32_t>& rBingoValues)
    {
        for(size_t row = 0; row < m_matrix.size(); ++row)
        {
            rBingoValues.clear();
            for(size_t column = 0; column < m_matrix[row].size(); ++column)
            {
                for(uint32_t value : m_markedValues)
                {
                    if(m_matrix[row][column] == value)
                    {
                        rBingoValues.push_back(value);
                        break;
                    }
                }
            }
            if(rBingoValues.size() == m_matrix[row].size())
            {
                std::cout<<"Horizontal Bingo!"<<std::endl;
                return true;
            }
        }
        return false;
    }

    bool CheckVertical(std::vector<uint32_t>& rBingoValues)
    {
        for(size_t column = 0; column < m_matrix.size(); ++column)
        {
            rBingoValues.clear();
            for(size_t row = 0; row < m_matrix.size(); ++row)
            {
                for(uint32_t value : m_markedValues)
                {
                    if(m_matrix[row][column] == value)
                    {
                        rBingoValues.push_back(value);
                        break;
                    }
                }
            }
            if(rBingoValues.size() == m_matrix.size())
            {
                std::cout<<"Vertical Bingo!"<<std::endl;
                return true;
            }
        }
        return false;
    }
private:
    std::vector<std::vector<uint32_t>> m_matrix; // [ROW][COLUMN]
    std::vector<uint32_t> m_markedValues;
};