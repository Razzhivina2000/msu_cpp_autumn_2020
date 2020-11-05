#pragma once

class BigInt
{
    int *val = nullptr;
    size_t len = 0;
    bool is_negative = false;
    
    BigInt my_abs(const BigInt &v1);
    BigInt abs_sum(const BigInt &v1, const BigInt &v2);
    BigInt abs_diff(const BigInt &v1, const BigInt &v2);
    BigInt abs_mul(const BigInt &v1, const BigInt &v2);
public:
    BigInt();
    BigInt(int x);
    BigInt(std::string s);
    BigInt(const BigInt &other);
    BigInt(BigInt &&other);
    
    BigInt& operator=(const BigInt &other);
    BigInt& operator=(BigInt &&other);
    BigInt operator-() const;
    BigInt operator+(const BigInt &v2);
    BigInt operator-(const BigInt &v2);
    BigInt operator*(const BigInt &v2) ;
    bool operator==(const BigInt &other) const;
    
    bool operator!=(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;
    
    friend std::ostream& operator<<(std::ostream& ostream, const BigInt& x);
    
    ~BigInt();
    
};
