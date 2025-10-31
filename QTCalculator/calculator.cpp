#include "calculator.h"
#include <cmath>

void Calculator::Set(Number n) {
    current_value_ = n;
}

Number Calculator::GetNumber() const {
    return current_value_;
}

void Calculator::Add(Number n) {
    current_value_ += n;
}

void Calculator::Sub(Number n) {
    current_value_ -= n;
}

void Calculator::Div(Number n) {
    current_value_ /= n;
}

void Calculator::Mul(Number n) {
    current_value_ *= n;
}

void Calculator::Pow(Number n) {
    current_value_ = std::pow(current_value_, n);
}

void Calculator::Save() {
    memory_state_ = true;
    memory_slot_ = current_value_;
}

void Calculator::Load() {
    current_value_ = memory_slot_;
}

bool Calculator::HasMem() const {
    return memory_state_;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(current_value_);
}
