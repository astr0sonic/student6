#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

bool isValidBracketSequence(const string& expression) {
    stack<char> bracketStack;
    unordered_map<char, char> matchingBrackets = {
        {')', '('},
        {']', '['},
        {'}', '{'},
        {'>', '<'}
    };

    for (char ch : expression) {
        if (ch == '(' || ch == '[' || ch == '{' || ch == '<') {
            bracketStack.push(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}' || ch == '>') {
            if (bracketStack.empty() || bracketStack.top() != matchingBrackets[ch]) {
                return false;
            }
            bracketStack.pop();
        }
    }

    return bracketStack.empty();
}
