#include "huffman.h"
#include <queue>
#include <map>
#include <vector>

struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : character(c), frequency(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->frequency > r->frequency;
    }
};

HuffmanNode* buildHuffmanTree(const std::string& text) {
    std::map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;
    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* node = new HuffmanNode('\0', left->frequency + right->frequency);
        node->left = left;
        node->right = right;
        pq.push(node);
    }

    return pq.top();
}

void generateCodes(HuffmanNode* root, std::string str, std::map<char, std::string>& huffmanCode) {
    if (!root)
        return;
    if (root->character != '\0') {
        huffmanCode[root->character] = str;
    }
    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

std::string encode(const std::string& text) {
    HuffmanNode* root = buildHuffmanTree(text);
    std::map<char, std::string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    std::string encoded = "";
    for (char c : text) {
        encoded += huffmanCode[c];
    }

    return encoded;
}

std::string decode(const std::string& encoded, std::map<char, std::string>& huffmanCode) {
    std::map<std::string, char> reverseHuffmanCode;
    for (auto pair : huffmanCode) {
        reverseHuffmanCode[pair.second] = pair.first;
    }

    std::string decoded = "";
    std::string currentCode = "";
    for (char bit : encoded) {
        currentCode += bit;
        if (reverseHuffmanCode.find(currentCode) != reverseHuffmanCode.end()) {
            decoded += reverseHuffmanCode[currentCode];
            currentCode = "";
        }
    }

    return decoded;
}
