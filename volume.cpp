#include "volume.h"

#include "volume.h"
#include <algorithm>

int getMaxVolume(int a, int b, int c, int n, int* arr) {
    int maxVolume = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int height = std::min(arr[i], arr[j]);
            int length = j - i;
            int volume = b * length * height;
            if (volume > maxVolume) {
                maxVolume = volume;
            }
        }
    }

    return maxVolume;
}
