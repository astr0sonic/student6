#include "max_value.h"
#include <algorithm>
#include <limits>

using namespace std;

double calculate(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return b != 0 ? a / b : numeric_limits<double>::lowest();
    }
    return numeric_limits<double>::lowest();
}

double calculateMaxValue(double* nums, int n) {
    if (n < 2) return numeric_limits<double>::lowest();

    vector<char> ops = { '+', '-', '*', '/' };
    double max_value = numeric_limits<double>::lowest();

    sort(nums, nums + n);
    do {
        for (char op1 : ops) {
            for (char op2 : ops) {
                for (char op3 : ops) {
                    double result = calculate(calculate(calculate(nums[0], nums[1], op1), nums[2], op2), nums[3], op3);
                    max_value = max(max_value, result);
                }
            }
        }
    } while (next_permutation(nums, nums + n));

    return max_value;
}