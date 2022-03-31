#pragma once

#include "suffix_array.h"
#include <string>
#include <vector>
#include <map>


namespace NSuffixTrees {

    class TSuffixArray;

    class TNode {
    public:
        TNode(std::string::iterator begin, std::string::iterator end);
        ~TNode() = default;

        std::string::iterator begin;
        std::string::iterator end;

        std::map< char, TNode* > to;
        TNode* suffixLink;
    };

    class TSuffixTree {
    public:
        TSuffixTree(std::string str);
        ~TSuffixTree();
        friend TSuffixArray;

    private:
        std::string text;
        TNode* root;

        TNode* needSufLink;
        TNode* activeNode;
        int remainder;
        int activeLen;
        std::string::iterator activeEdge;

        void TreeExtend(std::string::iterator toAdd);
        void DeleteTree(TNode* node);

        int GetEdgeLen(TNode* node, std::string::iterator pos) const;
        void AddSuffixLink(TNode* node);
        void DFS(TNode* node, std::vector<size_t>& result, size_t depth) const;
    };
} // namespace NSuffixTrees
