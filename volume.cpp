#include "volume.h"
#include <algorithm>

int getMaxVolume(int a, int b, int c, int n, int* arr) {
    int maxVolume = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int height = std::min(arr[i], arr[j]);
            if (height <= c) {
                int length = j - i;
                int volume = length * b * height;
                maxVolume = std::max(maxVolume, volume);
            }
        }
    }

    return maxVolume;
}