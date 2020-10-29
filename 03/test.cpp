#include <iostream>
#include <sstream>
#include "matrix.h"

void Test1() {
    Matrix m(3,5);
    assert(m.getRows() == 3);
    assert(m.getColumns() == 5);
}

void Test2() {
    Matrix m(3,5);
    Matrix m2(3,5);
    for (size_t i = 0; i < m.getRows(); ++i) {
        for (size_t j = 0; j < m.getColumns(); ++j) {
            m[i][j] = 1;
        }
    }
    for (size_t i = 0; i < m2.getRows(); ++i) {
        for (size_t j = 0; j < m2.getColumns(); ++j) {
            m2[i][j] = 3;
        }
    }
    m *= 3;
    assert(m == m2);
}

void Test3() {
    Matrix m(3,5);
    Matrix m2(3,5);
    for (size_t i = 0; i < m.getRows(); ++i) {
        for (size_t j = 0; j < m.getColumns(); ++j) {
            m[i][j] = 1;
        }
    }
    int k = 0;
    for (size_t i = 0; i < m2.getRows(); ++i) {
        for (size_t j = 0; j < m2.getColumns(); ++j) {
            m2[i][j] = k;
            k++;
        }
    }
    assert(m2[1][2] == 7);
    Matrix m3 = m2 + m;
    Matrix m4(3,5);
    for (size_t i = 0; i < m4.getRows(); ++i) {
        for (size_t j = 0; j < m4.getColumns(); ++j) {
            m4[i][j] = m2[i][j] + 1;
        }
    }
    assert(m3 == m4);
}

void Test4() {
    Matrix m(3,5);
    Matrix m2(4,5);
    assert(m != m2);
    Matrix m3(3,5);
    assert(m == m3);
    m[0][0] = 15;
    assert(m != m3);
    m3[0][0] = 3;
    m3 *= 5;
    assert(m == m3);
}

void Test5() {
    Matrix m(3,5);
    int k = 0;
    for (size_t i = 0; i < m.getRows(); ++i) {
        for (size_t j = 0; j < m.getColumns(); ++j) {
            m[i][j] = k;
            k++;
        }
    }
    std::stringstream ss;
    ss << m << std::endl;
    std::string row1, row2, row3;
    getline(ss, row1);
    getline(ss, row2);
    getline(ss, row3);
    assert(row1 == "0 1 2 3 4 ");
    assert(row2 == "5 6 7 8 9 ");
    assert(row3 == "10 11 12 13 14 ");
}

void Test6() {
    Matrix m(3,5);
    for (size_t i = 0; i < m.getRows(); ++i) {
        for (size_t j = 0; j < m.getColumns(); ++j) {
            m[i][j] = 1;
        }
    }
    Matrix m2 = m;
    m2 *= 3;
    Matrix m3(3,5);
    for (size_t i = 0; i < m3.getRows(); ++i) {
        for (size_t j = 0; j < m3.getColumns(); ++j) {
            m3[i][j] = 3;
        }
    }
    assert(m2 == m3);
    Matrix m4(4,6);
    m4 = m2;
    assert(m4 == m3);
}

int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    
    std::cout << "Success!\n";
    return 0;
}
