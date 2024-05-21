#include <iostream>
#include <vector>
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
    return 0 ;
}


double maxExpressionValue(vector<double>& nums, vector<char>& ops, int index = 1) {
    if (index == nums.size()) {
        return nums[0];
    }

    double maxValue = numeric_limits<double>::lowest();
    for (int i = index; i < nums.size(); ++i) {
        double a = nums[index - 1];
        double b = nums[index];

        for (char op : ops) {
            double result = calculate(a, b, op);

            vector<double> newNums = nums;
            newNums[index - 1] = result;
            newNums.erase(newNums.begin() + index);

            maxValue = max(maxValue, maxExpressionValue(newNums, ops, index));
        }
    }
    return maxValue;
}
