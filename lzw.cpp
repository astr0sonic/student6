#include "lzw.h"
#include <unordered_map>

std::vector<int> compress(const std::string& text) {
    std::unordered_map<std::string, int> dictionary;
    for (int i = 0; i <= 255; i++) {
        dictionary[std::string(1, i)] = i;
    }

    std::string w;
    std::vector<int> compressed;
    int dictSize = 256;

    for (char c : text) {
        std::string wc = w + c;
        if (dictionary.count(wc)) {
            w = wc;
        }
        else {
            compressed.push_back(dictionary[w]);
            dictionary[wc] = dictSize++;
            w = std::string(1, c);
        }
    }

    if (!w.empty()) {
        compressed.push_back(dictionary[w]);
    }

    return compressed;
}

std::string decompress(const std::vector<int>& compressed) {
    std::unordered_map<int, std::string> dictionary;
    for (int i = 0; i <= 255; i++) {
        dictionary[i] = std::string(1, i);
    }

    std::string w(1, compressed[0]);
    std::string decompressed = w;
    int dictSize = 256;
    std::string entry;

    for (size_t i = 1; i < compressed.size(); i++) {
        int k = compressed[i];
        if (dictionary.count(k)) {
            entry = dictionary[k];
        }
        else if (k == dictSize) {
            entry = w + w[0];
        }

        decompressed += entry;

        dictionary[dictSize++] = w + entry[0];

        w = entry;
    }

    return decompressed;
}