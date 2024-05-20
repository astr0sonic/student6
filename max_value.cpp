#include "max_value.h"
#include <algorithm>
#include <limits>
#include <vector>

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

double evaluateExpression(vector<double> nums, vector<char> ops) {
    double result = nums[0];
    for (int i = 0; i < ops.size(); ++i) {
        result = calculate(result, nums[i + 1], ops[i]);
    }
    return result;
}

void findMaxValue(vector<double> nums, vector<char>& ops, int index, double& max_value) {
    if (index == nums.size() - 1) {
        double value = evaluateExpression(nums, ops);
        max_value = max(max_value, value);
        return;
    }

    vector<char> operators = { '+', '-', '*', '/' };
    for (char op : operators) {
        ops[index] = op;
        findMaxValue(nums, ops, index + 1, max_value);
    }
}

double calculateMaxValue(double* nums, int n) {
    vector<double> numbers(nums, nums + n);
    double max_value = numeric_limits<double>::lowest();

    sort(numbers.begin(), numbers.end());
    do {
        vector<char> ops(n - 1);
        findMaxValue(numbers, ops, 0, max_value);
    } while (next_permutation(numbers.begin(), numbers.end()));

    return max_value;
}
