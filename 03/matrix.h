#pragma once

class Matrix
{
    int **matrix;
    const size_t rows;
    const size_t cols;
public:
    Matrix(size_t rows_, size_t cols_);
    size_t getRows();
    size_t getColumns();
    class Proxy {
        int *row_matrix;
        const size_t size;
    public:
        Proxy(int *row_matrix_, size_t cols);
        int& operator[](size_t j);
        const int& operator[](size_t j) const;
    };
    Proxy operator[](size_t i) const;
    const Matrix& operator*=(int val);
    Matrix operator+(const Matrix &other);
    bool operator==(const Matrix &other);
    bool operator!=(const Matrix &other);
    friend std::ostream& operator<<(std::ostream& ostream, const Matrix& m);
    ~Matrix();
};
