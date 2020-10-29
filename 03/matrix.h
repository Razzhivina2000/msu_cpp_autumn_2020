#pragma once

class Matrix
{
    int **matrix;
    size_t rows;
    size_t cols;
public:
    Matrix(size_t rows_, size_t cols_);
    Matrix(const Matrix &m);
    Matrix& operator=(const Matrix &m);
    size_t getRows() const;
    size_t getColumns() const;
    class Proxy {
        int *row_matrix;
        size_t size;
    public:
        Proxy(int *row_matrix_, size_t cols);
        int& operator[](size_t j);
        const int& operator[](size_t j) const;
    };
    Proxy operator[](size_t i) const;
    Matrix& operator*=(int val);
    Matrix operator+(const Matrix &other) const;
    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;
    friend std::ostream& operator<<(std::ostream& ostream, const Matrix& m);
    ~Matrix();
};
