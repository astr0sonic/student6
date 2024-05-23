#include "calculator.h"
#include <stack>
#include <string>
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <sstream>
#include <iostream>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isNumber(char c) {
    return std::isdigit(c) || c == '.';
}

int getPrecedence(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

double applyOperator(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0.0) throw std::runtime_error("Division by zero");
        return a / b;
    case '^': return std::pow(a, b);
    default: throw std::runtime_error("Invalid operator");
    }
}

void handleUnaryMinus(std::stack<double>& values) {
    if (values.empty()) throw std::runtime_error("Invalid expression");
    double value = values.top();
    values.pop();
    values.push(-value);
}

bool parseExpression(const std::string& expr, std::string& output) {
    std::stack<char> operators;
    std::stringstream result;
    bool expectOperand = true;

    for (size_t i = 0; i < expr.size(); ++i) {
        char token = expr[i];

        if (std::isspace(token)) {
            continue;
        }

        if (isNumber(token)) {
            if (!expectOperand) {
                return false;
            }
            while (i < expr.size() && (isNumber(expr[i]) || expr[i] == '.')) {
                result << expr[i++];
            }
            result << ' ';
            --i;
            expectOperand = false;
        }
        else if (token == '(') {
            operators.push(token);
            expectOperand = true;
        }
        else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                result << operators.top() << ' ';
                operators.pop();
            }
            if (operators.empty() || operators.top() != '(') {
                return false;
            }
            operators.pop();
            expectOperand = false;
        }
        else if (isOperator(token)) {
            if (token == '-' && expectOperand) {
                result << '0' << ' ';
            }
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(token)) {
                result << operators.top() << ' ';
                operators.pop();
            }
            operators.push(token);
            expectOperand = true;
        }
        else {
            return false;
        }
    }

    while (!operators.empty()) {
        if (operators.top() == '(') {
            return false;
        }
        result << operators.top() << ' ';
        operators.pop();
    }

    output = result.str();
    return true;
}

double evaluatePostfix(const std::string& postfix) {
    std::stack<double> values;
    std::stringstream ss(postfix);
    std::string token;

    while (ss >> token) {
        if (isNumber(token[0]) || (token.size() > 1 && isNumber(token[1]))) {
            values.push(std::stod(token));
        }
        else if (isOperator(token[0])) {
            if (values.size() < 2) {
                throw std::runtime_error("Invalid expression");
            }
            double b = values.top();
            values.pop();
            double a = values.top();
            values.pop();
            values.push(applyOperator(a, b, token[0]));
        }
    }

    if (values.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return values.top();
}

double calculate(const std::string& expr) {
    std::string postfix;
    if (!parseExpression(expr, postfix)) {
        throw std::runtime_error("Invalid expression");
    }
    return evaluatePostfix(postfix);
}
