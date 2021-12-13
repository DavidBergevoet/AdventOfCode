#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <iostream>
#include <sstream>
#include <vector>


/*
 * NOTE:
 * T must have the '<<' operator
 */
template<typename T>
class Matrix
{
public:
    Matrix(size_t rows = 0, size_t columns = 0);

    // At functions with range checking
    const std::vector<T>& At(size_t rowIndex) const;
    std::vector<T>& At(size_t rowIndex);

    const T& At(size_t rowIndex, size_t columnIndex) const;
    T& At(size_t rowIndex, size_t columnIndex);

    // Array operators
    const std::vector<T>& operator[](size_t rowIndex) const;
    std::vector<T>& operator[](size_t rowIndex);

    // Getters
    size_t GetRows() const;
    size_t GetColumns() const;

    // Setters
    bool SetColumns(size_t colums);

    // Other functions
    void Resize(size_t rows, size_t columns);

    bool AddRow(const std::vector<T>& rNewRow);

    std::string ToString() const;

private:
    size_t m_rows;
    size_t m_columns;
    std::vector<std::vector<T>> m_matrix;
};

template<typename T>
std::ostream& operator<<(std::ostream& rOs, const Matrix<T>& rMatrix);

#include "Matrix.tpp"

#endif // MATRIX_HPP_