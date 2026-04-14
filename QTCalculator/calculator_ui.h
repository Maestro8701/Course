#pragma once

#include <iostream>

#include "calculator.h"

class CalculatorUI {
public:
    CalculatorUI(Calculator& calc, std::ostream& out, std::ostream& err);
    
    bool Parse(std::istream& input) const;

private:
    bool ReadNumber(std::istream& input, Number& result) const;
    
private:
    Calculator& calc_;
    std::ostream& output_;
    std::ostream& error_;  
};
