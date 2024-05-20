#include <stdio.h>
#include <stdlib.h>

double performOperation(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return b != 0 ? a / b : 1e-9; 
    default: return 0;
    }
}

double recursiveMaxValue(double* nums, int n, int current) {
    if (current == n - 1) {
        return nums[current];
    }

    double maxValue = -1e9;

    for (int i = current + 1; i < n; i++) {
        double left = nums[current];
        double right = recursiveMaxValue(nums, n, i);

        double addResult = performOperation(left, right, '+');
        double subResult = performOperation(left, right, '-');
        double mulResult = performOperation(left, right, '*');
        double divResult = performOperation(left, right, '/');

        if (addResult > maxValue) maxValue = addResult;
        if (subResult > maxValue) maxValue = subResult;
        if (mulResult > maxValue) maxValue = mulResult;
        if (divResult > maxValue) maxValue = divResult;
    }

    return maxValue;
}

double calculateMaxValue(double* nums, int n) {
    if (n <= 0) return 0.0;
    return recursiveMaxValue(nums, n, 0);
}

