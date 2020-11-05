#include <iostream>
#include "bigint.h"

BigInt BigInt::my_abs(const BigInt &v1) {
    if(v1.is_negative) {
        return -v1;
    }
    return v1;
}

BigInt BigInt::abs_sum(const BigInt &v1, const BigInt &v2) {
    BigInt sum;
    sum.len = v1.len + 1;
    sum.val = new int[sum.len];
    sum.val[0] = 0;
    for (size_t i = 0; i < sum.len - 1; ++i)
    {
        if(i < v1.len) {
            sum.val[i] += v1.val[i];
        }
        if(i < v2.len) {
            sum.val[i] += v2.val[i];
        }
        sum.val[i + 1] = (sum.val[i] / 10);
        sum.val[i] %= 10;
    }
        
    if (sum.val[sum.len - 1] == 0) {
        sum.len--;
    }
    return sum;
}
    
BigInt BigInt::abs_diff(const BigInt &v1, const BigInt &v2) {
    BigInt dif;
    dif.len = v1.len + 1;
    dif.val = new int[dif.len];
    dif.val[0] = 0;
    for (size_t i = 0; i < dif.len - 1; ++i)
    {
        if(i < v1.len) {
            dif.val[i] += v1.val[i];
        }
        if(i < v2.len) {
            dif.val[i] -= v2.val[i];
        }
        if(dif.val[i] < 0) {
            dif.val[i + 1] = -1;
            dif.val[i] += 10;
        } else {
            dif.val[i + 1] = 0;
        }
    }
    for (size_t i = dif.len - 1; i > 0; --i) {
        if (dif.val[i] == 0) {
            dif.len--;
        } else {
            break;
        }
    }
    return dif;
}
    
BigInt BigInt::abs_mul(const BigInt &v1, const BigInt &v2) {
    BigInt mul;
    mul.len = v1.len + v2.len;
    mul.val = new int[mul.len];
    for (size_t i = 0; i < mul.len; ++i) {
        mul.val[i] = 0;
    }
    for (size_t i = 0; i < v2.len; ++i) {
        for (size_t j = 0; j < v1.len; ++j) {
            mul.val[i + j] += v1.val[j] * v2.val[i];
            mul.val[i + j + 1] += (mul.val[i + j] / 10);
            mul.val[i + j] %= 10;
        }
    }
    for (size_t i = mul.len - 1; i > 0; --i) {
        if (mul.val[i] == 0) {
            mul.len--;
        } else {
            break;
        }
    }
    return mul;
}

BigInt::BigInt() {}
    
BigInt::BigInt(int x) {
    int tmp = x;
    if(x == 0) {
        len = 1;
    }
    while(tmp) {
        tmp /= 10;
        len++;
    }
    if(x < 0) {
        is_negative = true;
        x = -x;
    }
    val = new int[len];
    for(size_t j = 0; j < len; ++j) {
        val[j] = x % 10;
        x /= 10;
    }
}
    
BigInt::BigInt(std::string s) {
    len = s.size();
    if(s[0] == '-') {
        is_negative = true;
        len--;
    }
    val = new int[len];
    for(size_t j = 0; j < len; ++j) {
        val[j] = s[len - j + is_negative - 1] - 48;
    }
}
    
BigInt::BigInt(const BigInt &other) : len(other.len), is_negative(other.is_negative) {
    val = new int[len];
    for(size_t j = 0; j < len; ++j) {
        val[j] = other.val[j];
    }
}
    
BigInt::BigInt(BigInt &&other) : val(other.val), len(other.len), is_negative(other.is_negative) {
    other.val = nullptr;
    other.len = 0;
    other.is_negative = false;
}
    
BigInt& BigInt::operator=(const BigInt &other) {
    if(this == &other) {
        return *this;
    }
    delete[] val;
    len = other.len;
    is_negative = other.is_negative;
    val = new int[len];
    for(size_t j = 0; j < len; ++j) {
        val[j] = other.val[j];
    }
    return *this;
}
    
BigInt& BigInt::operator=(BigInt &&other) {
    if(this == &other) {
        return *this;
    }
    delete[] val;
    len = other.len;
    is_negative = other.is_negative;
    val = other.val;
    other.val = nullptr;
    other.len = 0;
    other.is_negative = false;
    return *this;
}
    
BigInt BigInt::operator-() const {
    BigInt tmp(*this);
    tmp.is_negative = !is_negative;
    return tmp;
}
    
BigInt BigInt::operator+(const BigInt &v2) {
    if(is_negative) {
        if(v2.is_negative) {
            if(my_abs(*this) > my_abs(v2)) {
                return -abs_sum(-*this, -v2);
            } else {
                return -abs_sum(-v2, -*this);
            }
        }
        if(my_abs(*this) <= my_abs(v2)) {
            return abs_diff(v2, -*this);
        } else {
            return -abs_diff(-*this, v2);
        }
    }
    if(!v2.is_negative) {
        if(my_abs(*this) > my_abs(v2)) {
            return abs_sum(*this, v2);
        } else {
            return abs_sum(v2, *this);
        }
    }
    if(my_abs(*this) >= my_abs(v2)) {
        return abs_diff(*this, -v2);
    } else {
        return -abs_diff(-v2, *this);
    }
}
    
BigInt BigInt::operator-(const BigInt &v2) {
    return *this + (-v2);
}
    
BigInt BigInt::operator*(const BigInt &v2) {
    if(*this == 0 || v2 == 0) {
        return 0;
    }
    if(is_negative) {
        if(v2.is_negative) {
            if(my_abs(*this) > my_abs(v2)) {
                return abs_mul(-*this, -v2);
            } else {
                return abs_mul(-v2, -*this);
            }
        }
        if(my_abs(*this) <= my_abs(v2)) {
            return -abs_mul(v2, -*this);
        } else {
            return -abs_mul(-*this, v2);
        }
    }
    if(!v2.is_negative) {
        if(my_abs(*this) > my_abs(v2)) {
            return abs_mul(*this, v2);
        } else {
            return abs_mul(v2, *this);
        }
    }
    if(my_abs(*this) >= my_abs(v2)) {
        return -abs_mul(*this, -v2);
    } else {
        return -abs_mul(-v2, *this);
    }
}
    
bool BigInt::operator==(const BigInt &other) const {
    if(len != other.len || is_negative != other.is_negative) {
        return false;
    }
    bool ans = true;
    for (size_t i = 0; i < len; ++i) {
        if(val[i] != other.val[i]) {
            ans = false;
            break;
        }
    }
    return ans;
}
    
bool BigInt::operator!=(const BigInt &other) const {
    return !(*this==other);
}
    
bool BigInt::operator<=(const BigInt &other) const {
    if(is_negative ^ other.is_negative) {
        return is_negative;
    }
    if(len != other.len) {
        return (len < other.len) ^ is_negative;
    }
    bool ans = true;
    for (size_t i = len; i > 0; --i) {
        if((val[i - 1] > other.val[i - 1]) || (is_negative && val[i - 1] < other.val[i - 1])) {
            ans = false;
            break;
        }
    }
    return ans;
}
    
bool BigInt::operator<(const BigInt &other) const {
    return (*this<=other) && (*this!=other);
}
    
bool BigInt::operator>(const BigInt &other) const {
    return !(*this<=other);
}
    
bool BigInt::operator>=(const BigInt &other) const {
    return !(*this<other);
}
        
BigInt::~BigInt() {
    delete[] val;
}

std::ostream& operator<<(std::ostream& ostream, const BigInt& x)
{
    if(x.is_negative) {
        ostream << "-";
    }
    for(size_t j = x.len; j > 0; --j) {
        ostream << x.val[j - 1];
    }
    return ostream;
}
