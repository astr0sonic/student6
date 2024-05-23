#include "kmp.h"
#include <vector>
#include <string>

std::vector<int> computePrefixFunction(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> pi(m);
    int k = 0;
    pi[0] = 0;
    for (int i = 1; i < m; i++) {
        while (k > 0 && pattern[k] != pattern[i]) {
            k = pi[k - 1];
        }
        if (pattern[k] == pattern[i]) {
            k++;
        }
        pi[i] = k;
    }
    return pi;
}

std::vector<int> getIndices(const std::string& my_template, const std::string& text) {
    std::vector<int> result;
    if (my_template.empty() || text.empty()) {
        return result;
    }
    std::vector<int> pi = computePrefixFunction(my_template);
    int n = text.length();
    int m = my_template.length();
    int k = 0;
    for (int i = 0; i < n; i++) {
        while (k > 0 && my_template[k] != text[i]) {
            k = pi[k - 1];
        }
        if (my_template[k] == text[i]) {
            k++;
        }
        if (k == m) {
            result.push_back(i - m + 1);
            k = pi[k - 1];
        }
    }
    return result;
}
