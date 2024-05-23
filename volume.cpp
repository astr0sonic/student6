#include "volume.h"
#include <algorithm>

int getMaxVolume(int a, int b, int c, int n, int* arr) {
    std::sort(arr, arr + n);

    int maxHeight = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (arr[i] <= c) {
            maxHeight = arr[i];
            break;
        }
    }

    return a * b * maxHeight;
}