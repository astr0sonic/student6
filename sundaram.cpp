#include "sundaram.h"
#include <vector>

std::vector<int> sieve(int n) {
    int k = (n - 1) / 2;
    std::vector<int> primes;
    std::vector<bool> a(k + 1, true);

    for (int i = 1; i <= k; ++i) {
        for (int j = i; (i + j + 2 * i * j) <= k; ++j) {
            a[i + j + 2 * i * j] = false;
        }
    }

    if (n > 2) {
        primes.push_back(2);
    }

    for (int i = 1; i <= k; ++i) {
        if (a[i]) {
            primes.push_back(2 * i + 1);
        }
    }

    return primes;
}