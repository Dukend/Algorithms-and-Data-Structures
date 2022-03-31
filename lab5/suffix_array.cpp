#include "suffix_array.h"
#include <algorithm>

namespace NSuffixTrees {
    TSuffixArray::TSuffixArray(const TSuffixTree& tree) :
        text(tree.text),
        array()
    {
        tree.DFS(tree.root, array, 0);
    }

    std::vector<size_t> TSuffixArray::Find(const std::string& pattern) {
        std::pair<std::vector<size_t>::iterator, std::vector<size_t>::iterator> range(array.begin(), array.end());
        for (size_t i = 0; i < pattern.size() && range.first != range.second; ++i) {
            range = equal_range(range.first, range.second, std::numeric_limits<size_t>::max(), [this, &pattern, &i] (size_t index1, size_t index2) -> bool {
                if (index1 == std::numeric_limits<size_t>::max()) {
                    return pattern[i] < text[i + index2];
                } else {
                    return text[i + index1] < pattern[i];
                }
            });
        }

        std::vector<size_t> result(range.first, range.second);
        std::sort(result.begin(), result.end());

        return result;
    }
} // namespace NSuffixTrees