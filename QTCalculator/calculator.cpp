#include <iostream>
#include <cmath>

#include "calculator.h"

bool ReadNumber(Number& operand) {
    if (!(std::cin >> operand)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    return true;
}

bool RunCalculatorCycle() {
    Number current_value;

    if (!(ReadNumber(current_value))) {
        return false;    
    }

    Number memory_slot;
    bool memory_state = false;
    std::string command;

    while (true) {
        if (!(std::cin >> command)) {
            return false;
        }

        if (command == "+") {
            Number operand;
            if (!(ReadNumber(operand))) {
                return false; 
            }
            current_value += operand; 
        } else if (command == "=") {
            std::cout << current_value << std::endl;
        } else if (command == "-") {
            Number operand;
            if (!(ReadNumber(operand))) {
                return false;
            }
            current_value -= operand;
        } else if (command == "*") {
            Number operand;
            if (!(ReadNumber(operand))) {
                return false;
            }
            current_value *= operand;
        } else if (command == "/") {
            Number operand;
            if (!(ReadNumber(operand))) {
                return false; 
            } 
            current_value /= operand;
        } else if (command == "**") {      
            Number operand;
            if (!(ReadNumber(operand))) {
                return false;
            }  
            current_value = std::pow(current_value, operand);
        } else if (command == ":") {      
            Number operand;
            if (!(ReadNumber(operand))) {
                return false; 
            }  
            current_value = operand;
        } else if (command == "c") {      
            current_value = 0;
        } else if (command == "s") {      
            memory_state = true;
            memory_slot = current_value;
        } else if (command == "l") {      
            if(!memory_state) {
                std::cerr << "Error: Memory is empty";
                return false;
            }
            current_value = memory_slot;
        } else if (command == "q") {
            return true; 
        } else {
            std::cerr << "Error: Unknown token " << command << std::endl;
            return false; 
        }
    }
}
