#include "bracket.h"
#include <stack>
#include <unordered_map>

bool checkBrackets(const std::string& s) {
    std::stack<char> stack;
    std::unordered_map<char, char> brackets = {
        {')', '('},
        {']', '['},
        {'}', '{'},
        {'>', '<'}
    };

    for (char ch : s) {
        if (brackets.count(ch)) {
            if (stack.empty() || stack.top() != brackets[ch]) {
                return false;
            }
            stack.pop();
        }
        else if (ch == '(' || ch == '[' || ch == '{' || ch == '<') {
            stack.push(ch);
        }
    }

    return stack.empty();
}
