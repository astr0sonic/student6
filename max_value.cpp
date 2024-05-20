#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

double calculateMaxValue(double* nums, int n) {
    double calculate(double a, double b, char op) {
        switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : numeric_limits<double>::lowest();
        }
        return numeric_limits<double>::lowest();
    }

    vector<char> ops = { '+', '-', '*', '/' };
    double max_value = numeric_limits<double>::lowest();

    sort(nums, nums + n);
    do {
        vector<char> current_ops(n - 1);
        function<void(int)> try_operations = [&](int index) {
            if (index == n - 1) {
                double result = nums[0];
                for (int i = 1; i < n; ++i) {
                    result = calculate(result, nums[i], current_ops[i - 1]);
                }
                max_value = max(max_value, result);
                return;
            }

            for (char op : ops) {
                current_ops[index] = op;
                try_operations(index + 1);
            }
            };
        try_operations(0);
    } while (next_permutation(nums, nums + n));

    return max_value;
}

int main() {
    double nums[] = { 1.0, 2.0, 3.0, 4.0 };
    int n = sizeof(nums) / sizeof(nums[0]);

    double result = calculateMaxValue(nums, n);
    cout << "Maximum value: " << result << endl;

    return 0;
}
