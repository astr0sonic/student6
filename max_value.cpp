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
    return 0; // не должно достигаться
}

double maxExpressionValue(std::vector<double>& nums, const std::vector<char>& ops, int index = 1) {
    if (index == nums.size()) {
        return nums[0];
    }

    double maxValue = std::numeric_limits<double>::lowest();
    for (int i = index; i < nums.size(); ++i) {
        // Сохраняем текущие значения
        double a = nums[index - 1];
        double b = nums[index];

        // Пробуем все операции
        for (char op : ops) {
            // Вычисляем текущее значение
            double result = calculate(a, b, op);

            // Создаем новый массив чисел
            std::vector<double> newNums = nums;
            newNums[index - 1] = result;
            newNums.erase(newNums.begin() + index);

            // Рекурсивный вызов
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