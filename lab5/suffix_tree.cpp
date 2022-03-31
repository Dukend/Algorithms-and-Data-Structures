#include "suffix_tree.h"

namespace NSuffixTrees {
    //// TNode
    TNode::TNode(std::string::iterator begin, std::string::iterator end) :
        begin(begin),
        end(end),
        suffixLink(0)
    {}

    //// TSuffixTree
    TSuffixTree::TSuffixTree(std::string str) :
        text(str),
        root(new TNode(text.end(), text.end())),
        remainder(0)
    {
        activeEdge = text.begin();
        activeNode = needSufLink = root->suffixLink = root;
        activeLen = 0;

        for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
            TreeExtend(it);
        }
    }

    TSuffixTree::~TSuffixTree() {
        DeleteTree(root);
    };

    void TSuffixTree::DeleteTree(TNode* node) {
        for (std::map< char, TNode* >::iterator it = node->to.begin(); it != node->to.end(); ++it) {
            DeleteTree(it->second);
        }
        delete node;
    }

    int TSuffixTree::GetEdgeLen(TNode* node, std::string::iterator pos) const {
        return std::min(node->end, pos + 1) - node->begin;
    }

    void TSuffixTree::TreeExtend(std::string::iterator toAdd) {
        needSufLink = root;
        ++remainder;

        while (remainder) {
            if (!activeLen) activeEdge = toAdd;

            TNode *next = NULL;
            std::map< char, TNode* >::iterator it = activeNode->to.find(*activeEdge);
            if (it != activeNode->to.end()) next = it->second;

            if (!next) {
                TNode* leaf = new TNode(toAdd, text.end());
                activeNode->to[*activeEdge] = leaf;
                AddSuffixLink(activeNode);
            } else {
                if (activeLen >= GetEdgeLen(next, toAdd)) {
                    activeEdge += GetEdgeLen(next, toAdd);
                    activeLen -= GetEdgeLen(next, toAdd);
                    activeNode = next;
                    continue;
                }

                if (*(next->begin + activeLen) == *toAdd) {
                    ++activeLen;
                    AddSuffixLink(activeNode);
                    break;
                }

                TNode* split = new TNode(next->begin, next->begin + activeLen);
                TNode* leaf = new TNode(toAdd, text.end());
                activeNode->to[*activeEdge] = split;

                split->to[*toAdd] = leaf;
                next->begin += activeLen;
                split->to[*next->begin] = next;
                AddSuffixLink(split);
            }

            --remainder;
            if (activeNode == root && activeLen > 0) {
                --activeLen;
                activeEdge = toAdd - remainder + 1;
            } else {
                if (activeNode->suffixLink) {
                    activeNode = activeNode->suffixLink;
                } else {
                    activeNode = root;
                }
            }
        }
    }

    void TSuffixTree::AddSuffixLink(TNode* node) {
        if (needSufLink != root) needSufLink->suffixLink = node;
        needSufLink = node;
    }

    void TSuffixTree::DFS(TNode* node, std::vector<size_t>& result, size_t depth) const {
        if (node->to.empty()) {
            result.push_back(text.size() - depth);
            return;
        }
        for (std::map<char, TNode*>::iterator it = node->to.begin(); it != node->to.end(); ++it) {
            DFS(it->second, result, depth + it->second->end - it->second->begin);
        }
    }
} // namespace NSuffixTrees
