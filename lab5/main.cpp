#include <iostream>
#include <string>
#include "suffix_tree.h"
#include "suffix_array.h"

int main() {
    std::ios::sync_with_stdio(false);

    std::string text, pattern;
    std::cin >> text;

    NSuffixTrees::TSuffixTree suffixTree(text + "$");
    NSuffixTrees::TSuffixArray suffixArray(suffixTree);

    size_t patCount = 0;
    while (std::cin >> pattern) {
        ++patCount;
        std::vector<size_t> result = suffixArray.Find(pattern);
        if (!result.empty()) {
            std::cout << patCount << ": ";
            for (size_t i = 0; i < result.size(); ++i) {
                std::cout << result[i] + 1;
                if (i < result.size() -  1) std::cout << ", ";
            }
            std::cout << "\n";
        }
    }

    return 0;
}