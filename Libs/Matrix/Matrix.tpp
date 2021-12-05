template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) : m_rows(rows), m_columns(columns)
{
    m_matrix.resize(rows);
    for(size_t row = 0; row < rows; ++row)
    {
        m_matrix[row].resize(columns);
    }
}

template<typename T>
std::string Matrix<T>::ToString() const
{
    std::stringstream ss;
    ss << "Matrix<" << m_rows << ", " << m_columns << ">\n";
    for(size_t row = 0; row < m_rows; ++row)
    {
        for(size_t column = 0; column < m_columns; ++ column)
        {
            ss << m_matrix[row][column] << " | ";
        }
        ss << "\n";
    }
    return ss.str();
}

template<typename T>
const std::vector<T>& Matrix<T>::At(size_t rowIndex) const
{
    if(rowIndex >= m_rows)
        throw std::out_of_range("Row index out of range!");

    return m_matrix[rowIndex];
}

template<typename T>
std::vector<T>& Matrix<T>::At(size_t rowIndex)
{
    if(rowIndex >= m_rows)
        throw std::out_of_range("Row index out of range!");

    return m_matrix[rowIndex];
}

template<typename T>
const T& Matrix<T>::At(size_t rowIndex, size_t columnIndex) const
{
    if(rowIndex >= m_rows)
        throw std::out_of_range("Row index out of range!");
    if(columnIndex >= m_columns)
        throw std::out_of_range("Column index out of range!");
    return m_matrix[rowIndex][columnIndex];
}

template<typename T>
T& Matrix<T>::At(size_t rowIndex, size_t columnIndex)
{
    if(rowIndex >= m_rows)
        throw std::out_of_range("Row index out of range!");
    if(columnIndex >= m_columns)
        throw std::out_of_range("Column index out of range!");
    return m_matrix[rowIndex][columnIndex];
}

template<typename T>
const std::vector<T>& Matrix<T>::operator[](size_t rowIndex) const
{
    return m_matrix[rowIndex];
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](size_t rowIndex)
{
    return m_matrix[rowIndex];
}

template<typename T>
size_t Matrix<T>::GetRows() const
{
    return m_rows;
}

template<typename T>
size_t Matrix<T>::GetColumns() const
{
    return m_columns;
}

template<typename T>
void Matrix<T>::Resize(size_t rows, size_t columns)
{
    m_matrix.resize(rows);
    for(size_t row = 0; row < rows; ++row)
    {
        m_matrix[row].resize(columns);
    }
    m_rows = rows;
    m_columns = columns;
}
