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

double calculateMaxValue(double* nums, int n) {
    if (n < 2) return numeric_limits<double>::lowest();

    vector<char> ops = { '+', '-', '*', '/' };
    double max_value = numeric_limits<double>::lowest();
    vector<char> current_ops(n - 1);

    sort(nums, nums + n);
    do {
        vector<int> indices(n - 1, 0);

        while (true) {
            for (int i = 0; i < n - 1; ++i) {
                current_ops[i] = ops[indices[i]];
            }

            double result = evaluateExpression(vector<double>(nums, nums + n), current_ops);
            max_value = max(max_value, result);

            int pos = n - 2;
            while (pos >= 0 && indices[pos] == 3) {
                indices[pos] = 0;
                --pos;
            }

            if (pos < 0) break;

            ++indices[pos];
        }
    } while (next_permutation(nums, nums + n));

    return max_value;
}