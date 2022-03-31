#pragma once

#include "suffix_tree.h"
#include <vector>
#include <string>

namespace NSuffixTrees {
    class TSuffixTree;

    class TSuffixArray {
    public:
        TSuffixArray(const TSuffixTree& tree);
        ~TSuffixArray() = default;

        std::vector<size_t> Find(const std::string& pattern);
    private:
        std::string text;
        std::vector<size_t> array;
    };
}