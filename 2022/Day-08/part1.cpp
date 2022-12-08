#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

class Tree
{
public:
Tree(uint height=0):m_height(height){}

uint m_height = 0;
bool m_visible = false;
};

std::ostream& operator<<(std::ostream& os, const Tree& rTree) 
{
    if(rTree.m_visible)
    {
        os<<"+";
    }
    else
    {
        os<<"-";
    }
    os<<rTree.m_height;
    return os;
}

int main(int argc, char const *argv[])
{
    std::string filePath = "input.txt";

    FileHandler file(filePath);
    Matrix<Tree> matrix;

    if (file.IsOpen())
    {
        // Read the file
        std::string line;
        while(file.GetLine(line))
        {
            if(matrix.GetColumns() != line.size())
            {
                matrix.SetColumns(line.size());
            }
            std::vector<Tree> treeLine;
            for(const char& rChar : line)
            {
                treeLine.push_back(Tree(rChar-'0'));
            }
            matrix.AddRow(treeLine);
        }
    }

    auto outside = matrix.GetOutsidePoints();

    for(const auto& point : outside)
    {
        matrix[point].m_visible = true;
    }

    // Left side    
    for(uint row = 1; row < matrix.GetRows(); ++row)
    {
        int heighest = matrix[row][0].m_height;
        for(uint col = 1; col < matrix.GetColumns(); ++col)
        {
            if(matrix[row][col].m_height > heighest)
            {
                heighest = matrix[row][col].m_height;
                matrix[row][col].m_visible = true;
            }
        }
    }

    // Bottom
    for(uint col = 1; col < matrix.GetColumns(); ++col)
    {
        int heighest = matrix[0][col].m_height;
        for(uint row = 1; row < matrix.GetRows(); ++row)
        {
            if(matrix[row][col].m_height > heighest)
            {
                heighest = matrix[row][col].m_height;
                matrix[row][col].m_visible = true;
            }
        }
    }

    // Right
    for(uint row = 1; row < matrix.GetRows(); ++row)
    {
        int heighest = matrix[row][matrix.GetColumns()-1].m_height;
        for(int col = matrix.GetColumns()-2; col >=0; --col)
        {
            if(matrix[row][col].m_height > heighest)
            {
                heighest = matrix[row][col].m_height;
                matrix[row][col].m_visible = true;
            }
        }
    }

    // Top
    for(uint col = 1; col < matrix.GetColumns(); ++col)
    {
        int heighest = matrix[matrix.GetRows()-1][col].m_height;
        for(int row = matrix.GetRows()-2; row >= 0 ; --row)
        {
            if(matrix[row][col].m_height > heighest)
            {
                heighest = matrix[row][col].m_height;
                matrix[row][col].m_visible = true;
            }
        }
    }

    // std::cout<<matrix<<std::endl;

    uint totalVisible = 0;
    for(uint row = 0; row < matrix.GetRows(); ++row)
    {
        for(uint col = 0; col < matrix.GetColumns(); ++col)
        {
            if(matrix[row][col].m_visible)
            {
                totalVisible++;
            }
        }
    }

    std::cout<<"Total visible: "<<totalVisible<<std::endl;

    return 0;
}