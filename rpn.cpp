#include "rpn.h"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <cctype>

double calculateRPN(const std::string& expr) {
    std::stack<double> stack;
    std::istringstream tokens(expr);
    std::string token;

    while (tokens >> token) {
        if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && std::isdigit(token[1]))) {
            stack.push(std::stod(token));
        }
        else {
            if (stack.size() < 2) {
                throw std::invalid_argument("Invalid expression");
            }
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();

            if (token == "+") {
                stack.push(a + b);
            }
            else if (token == "-") {
                stack.push(a - b);
            }
            else if (token == "*") {
                stack.push(a * b);
            }
            else if (token == "/") {
                stack.push(a / b);
            }
            else {
                throw std::invalid_argument("Invalid operator: " + token);
            }
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid expression");
    }

    return stack.top();
}
