// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include "bst.h"

namespace {
    std::string to_lower(const std::string& str) {
        std::string lower_str;
        lower_str.reserve(str.size());
        for (const unsigned char c : str) {
            lower_str += std::tolower(c);
        }
        return lower_str;
    }

    bool is_letter(char c) {
        return std::isalpha(static_cast<unsigned char>(c));
    }

} // namespace

void makeTree(BST<std::string>& tree, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file '" << filename << "'\n";
        return;
    }

    std::string current_word;
    current_word.reserve(32);

    char ch;
    while (file.get(ch)) {
        if (is_letter(ch)) {
            current_word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        } else if (!current_word.empty()) {
            tree.insert(current_word);
            current_word.clear();
        }
    }

    if (!current_word.empty()) {
        tree.insert(current_word);
    }
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequencies = tree.getFrequencies();

    std::sort(frequencies.begin(), frequencies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    std::ofstream outputFile("freq.txt");
    if (!outputFile) {
        std::cerr << "Error opening result file!" << std::endl;
        return;
    }
    for (const auto& pair : frequencies) {
        std::cout << pair.first << " " << pair.second << std::endl;
        outputFile << pair.first << " " << pair.second << std::endl;
    }

    outputFile.close();
}
