#include "calculator.h"

#include <iostream>
#include <string>

using namespace std::literals;

bool ReadNumber(Number& result) {
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected"s << std::endl;
        return false;
    }
    return true;
}

bool RunCalculatorCycle() {
    Number init_number;
    if (!ReadNumber(init_number)) {
        return false;
    }

    Calculator calc;
    calc.Set(init_number);

    std::string token;
    while(std::cin >> token) {
        Number right;
        if (token == "+"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Add(right);
        } else if (token == "-"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Sub(right);
        } else if (token == "*"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Mul(right);
        } else if (token == "/"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Div(right);
        } else if (token == "**"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Pow(right);
        } else if (token == "s"s) {
            calc.Save();
        } else if (token == "l"s) {
            if (!calc.HasMem()) {
                std::cerr << "Error: Memory is empty"s << std::endl;
                break;
            }
            calc.Load();
        } else if (token == "="s) {
            std::cout << calc.GetNumberRepr() << std::endl;
        } else if (token == "c"s) {
            calc.Set(0);
        } else if (token == "n"s) {
            calc.Set(-calc.GetNumber());
        } else if (token == ":"s) {
            if (!ReadNumber(right)) {
                break;
            }
            calc.Set(right);
        } else if (token == "q"s) {
            return true;
        } else {
            std::cerr << "Error: Unknown token "s << token << std::endl;
            break;
        }
    }
    return false;
}

constexpr int CALCULATION_ERROR = 1;

int main() {
    std::string type;
    std::cin >> std::ws;

    if (!RunCalculatorCycle()) {
        std::cerr << "Program failed! Error code: " << CALCULATION_ERROR << std::endl;
    }
}
