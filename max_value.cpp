#include "max_value.h"
#include <algorithm>
#include <vector>
#include <limits> 

double calculate(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return b != 0 ? a / b : std::numeric_limits<double>::lowest();
    }
    return 0;
}

double maxExpressionValue(std::vector<double>& nums, const std::vector<char>& ops, int index = 1) {
    if (index == nums.size()) {
        return nums[0];
    }

    double maxValue = std::numeric_limits<double>::lowest();
    for (int i = index; i < nums.size(); ++i) {

        double a = nums[index - 1];
        double b = nums[index];

        for (char op : ops) {
            double result = calculate(a, b, op);

            std::vector<double> newNums = nums;
            newNums[index - 1] = result;
            newNums.erase(newNums.begin() + index);

            maxValue = std::max(maxValue, maxExpressionValue(newNums, ops, index));
        }
    }
    return maxValue;
}

double calculateMaxValue(double* nums, int n) {
    std::vector<double> numVec(nums, nums + n);
    std::vector<char> ops = { '+', '-', '*', '/' };

    return maxExpressionValue(numVec, ops);
}