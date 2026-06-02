#pragma once
#include <iostream>
#include <numeric>   
#include <compare>  
#include <algorithm> 
#include <stdexcept> 

class Rational {
public:
    Rational() = default;                          
    Rational(int value)                              
        : numerator_(value), denominator_(1) {}
    Rational(int numerator, int denominator)       
        : numerator_(numerator), denominator_(denominator) {
        if (denominator_ == 0) throw std::invalid_argument("denominator is zero"); 
        Reduction();
    }
    Rational(const Rational&) = default;           

    /* ---------- присваивание ---------- */
    Rational& operator=(const Rational&) = default; 
    Rational& operator=(int value) {               
        numerator_ = value;
        denominator_ = 1;
        return *this;
    }

    Rational& operator+=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ + denominator_ * r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }
    Rational& operator-=(const Rational& r) {
        numerator_ = numerator_ * r.denominator_ - denominator_ * r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }
    Rational& operator*=(const Rational& r) {
        numerator_ *= r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }
    Rational& operator/=(const Rational& r) {
        if (r.numerator_ == 0) throw std::invalid_argument("division by zero"); 
        numerator_ *= r.denominator_;
        denominator_ *= r.numerator_;
        Reduction();
        return *this;
    }

    Rational operator+() const { return *this; }
    Rational operator-() const { return Rational(-numerator_, denominator_); }

    explicit operator double() const {
        return static_cast<double>(numerator_) / denominator_;
    }
    Rational Inv() const { return {denominator_, numerator_}; }
    int GetNumerator() const { return numerator_; }
    int GetDenominator() const { return denominator_; }

    friend std::ostream& operator<<(std::ostream&, const Rational&);
    friend std::istream& operator>>(std::istream&, Rational&);

private:
    void Reduction() {                       // <-- ИЗМЕНЕНО: теперь приватный
        if (denominator_ < 0) {            // минус всегда в числителе
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int d = std::gcd(numerator_, denominator_);
        numerator_ /= d;
        denominator_ /= d;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    if (r.denominator_ == 1) os << r.numerator_;
    else os << r.numerator_ << " / " << r.denominator_;
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int num;
    if (!(is >> num)) return is;          
    char sep = 0;
    is >> sep;
    if (!is || sep != '/') {               
        is.clear();
        if (sep) is.unget();                
        r = Rational(num, 1);
        return is;
    }
    int den;
    if (!(is >> den) || den == 0) {       
        is.setstate(std::ios::failbit);
        return is;
    }
    r = Rational(num, den);
    return is;
}

inline auto operator<=>(const Rational& lhs, const Rational& rhs) {
    return static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator() <=>
           static_cast<int64_t>(rhs.GetNumerator()) * lhs.GetDenominator();
}

inline bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() ==
           lhs.GetDenominator() * rhs.GetNumerator();
}

inline Rational operator+(const Rational& a, const Rational& b) {
    Rational tmp(a); tmp += b; return tmp;
}
inline Rational operator-(const Rational& a, const Rational& b) {
    Rational tmp(a); tmp -= b; return tmp;
}
inline Rational operator*(const Rational& a, const Rational& b) {
    Rational tmp(a); tmp *= b; return tmp;
}
inline Rational operator/(const Rational& a, const Rational& b) {
    Rational tmp(a); tmp /= b; return tmp;
}
