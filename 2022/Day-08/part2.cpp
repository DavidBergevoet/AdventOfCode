#include <iostream>
#include <vector>

#include "FileHandler.hpp"
#include "Matrix.hpp"

class Tree
{
public:
Tree(uint height=0):m_height(height){}

uint m_height = 0;
uint m_viewDistance = 0;
};

std::ostream& operator<<(std::ostream& os, const Tree& rTree) 
{
    os<<rTree.m_height<<"-"<<rTree.m_viewDistance;
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

    for(uint row = 1; row < matrix.GetRows()-1; row++)
    {
        for(uint col = 1; col < matrix.GetColumns()-1; col++)
        {
            std::vector<uint>distances(4);
            // Left of the point
            int counter = col;
            while(counter > 0)
            {
                distances[0]+=1;
                counter--;
                if(matrix[row][col].m_height <= matrix[row][counter].m_height)
                    break;
            }

            // Right of the point
            counter = col;
            while(counter < matrix.GetColumns())
            {
                distances[1]+=1;
                counter++;
                if(matrix[row][col].m_height <= matrix[row][counter].m_height)
                    break;
            }

            // Top of the point
            counter = row;
            while(counter > 0)
            {
                distances[2]+=1;
                counter--;
                if(matrix[row][col].m_height <= matrix[counter][col].m_height)
                    break;
            }

            // Bottom of the point
            counter = row;
            while(counter < matrix.GetRows()-1)
            {
                distances[3]+=1;
                counter++;
                if(matrix[row][col].m_height <= matrix[counter][col].m_height)
                    break;
            }

            matrix[row][col].m_viewDistance = distances[0] * distances[1] * distances[2] * distances[3];
        }
    }


    // std::cout<<matrix<<std::endl;

    uint max = 0;
    for(uint row = 0; row < matrix.GetRows(); ++row)
    {
        for(uint col = 0; col < matrix.GetColumns(); ++col)
        {
            if(matrix[row][col].m_viewDistance > max)
            {
                max = matrix[row][col].m_viewDistance;
            }
        }
    }

    std::cout<<"Max: "<<max<<std::endl;

    return 0;
}