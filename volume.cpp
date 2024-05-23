#include "volume.h"
#include <algorithm>

int getMaxVolume(int a, int b, int c, int n, int* arr) {
    int maxHeight = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] <= c) {
            maxHeight = std::max(maxHeight, arr[i]);
        }
    }
    return a * b * maxHeight;
}