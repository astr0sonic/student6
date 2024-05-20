#include <stdio.h>
#include <stdlib.h>

double performOperation(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return b != 0 ? a / b : 1e-9;  // Обработка деления на ноль
    default: return 0;
    }
}

double calculateMaxValue(double* nums, int n) {
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    double maxValue = -1e9;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double a = nums[i];
            double b = nums[j];

            double remaining[n - 1];
            int k = 0;
            for (int l = 0; l < n; l++) {
                if (l != i && l != j) {
                    remaining[k++] = nums[l];
                }
            }

            char ops[] = { '+', '-', '*', '/' };
            for (int op = 0; op < 4; op++) {
                remaining[n - 2] = performOperation(a, b, ops[op]);
                double result = calculateMaxValue(remaining, n - 1);
                if (result > maxValue) {
                    maxValue = result;
                }
            }
        }
    }

    return maxValue;
}