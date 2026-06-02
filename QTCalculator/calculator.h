
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"


using Error = std::string;

template<typename Number>
class Calculator {
public:

void Set(Number n) {
    current_value_ = n;
}

Number GetNumber() const {
    return current_value_;
}

std::optional<Error> Add(Number n) {    
    current_value_ += n;
    return std::nullopt;
}

std::optional<Error> Sub(Number n) {
    current_value_ -= n;
    return std::nullopt;
}

std::optional<Error> Div(Number n) {
    if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
        if(n == 0) {
            return std::string("Division by zero");
        } else {
            current_value_ /= n;
            return std::nullopt;
        }
    }
    current_value_ /= n;
        return std::nullopt;
}

std::optional<Error> Mul(Number n) {
    current_value_ *= n;
    return std::nullopt;
}

    std::optional<Error> Pow(Number n) {
        if constexpr (std::is_same_v<Number, Rational>) {
            // Для Rational использовать глобальную Pow
            if (n.GetDenominator() != 1) {
                return std::string("Fractional power is not supported");
            }
            if (current_value_ == Rational{0} && n == Rational{0}) {
                return std::string("Zero power to zero");
            }
            current_value_ = ::Pow(current_value_, n);  // Вызов для Rational
            return std::nullopt;
        }
        else if constexpr (std::is_integral_v<Number>) {
            // Для целых чисел использовать IntegerPow
            if (n < 0) {
                return std::string("Integer negative power");
            }
            if (current_value_ == Number{0} && n == Number{0}) {
                return std::string("Zero power to zero");
            }
            current_value_ = IntegerPow(current_value_, n);  // Используем IntegerPow
            return std::nullopt;
        }
        else {  // Для double, float и т.д.
            current_value_ = std::pow(static_cast<double>(current_value_), static_cast<double>(n));
            return std::nullopt;
        }
    }


std::string GetNumberRepr() const {
    return std::to_string(current_value_);
}

void Save() {
    mem_ = current_value_;
}

void Load() {
    if (mem_)
        current_value_ = *mem_;
}

bool GetHasMem() const {
    return mem_.has_value();
}

private:
    Number current_value_;
    std::optional<Number> mem_;

};



