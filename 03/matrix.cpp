#include <iostream>
#include "matrix.h"

Matrix::Matrix(size_t rows_, size_t cols_) : rows(rows_), cols(cols_) {
    matrix = new int*[rows];
    for (size_t i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = 0;
        }
    }
}
size_t Matrix::getRows() {
    return rows;
}
size_t Matrix::getColumns() {
    return cols;
}

Matrix::Proxy::Proxy(int *row_matrix_, size_t cols): row_matrix(row_matrix_), size(cols) {}
int& Matrix::Proxy::operator[](size_t j) {
    if(j >= size) {
        throw std::out_of_range("");
    }
    return row_matrix[j];
}
const int& Matrix::Proxy::operator[](size_t j) const {
    return row_matrix[j];
}

Matrix::Proxy Matrix::operator[](size_t i) const {
    if(i >= rows) {
        throw std::out_of_range("");
    }
    return Proxy(matrix[i], cols);
}

const Matrix& Matrix::operator*=(int val) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            matrix[i][j] = matrix[i][j] * val;
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &other) {
    assert(other.rows == rows && other.cols == cols);
    Matrix tmp(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            tmp.matrix[i][j] = matrix[i][j] + other[i][j];
        }
    }
    return tmp;
}

bool Matrix::operator==(const Matrix &other) {
    if(rows != other.rows || cols != other.cols) {
        return false;
    }
    bool ans = true;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if(matrix[i][j] != other.matrix[i][j]) {
                ans = false;
                break;
            }
        }
    }
    return ans;
}

bool Matrix::operator!=(const Matrix &other) {
    return !(*this==other);
}

Matrix::~Matrix() {
    for (size_t i = 0; i < rows; ++i)
        delete[] matrix[i];
    delete[] matrix;
}

std::ostream& operator<<(std::ostream& ostream, const Matrix& m)
{
    for (size_t i = 0; i < m.rows; ++i) {
        for (size_t j = 0; j < m.cols; ++j) {
            ostream << m[i][j] << " ";
        }
        ostream << "\n";
    }
    return ostream;
}
