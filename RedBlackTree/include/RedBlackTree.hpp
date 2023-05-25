#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "Node.hpp"
#include "Item.hpp"

#include <string>
#include <vector>
#include <iostream>

class TRedBlackTree
{
    protected:

        int Compare(const std::string& str1, const std::string& str2);

        TNode* Left(TNode* node);
        TNode* Right(TNode* node);

        TNode* LeftRotation(TNode* node);
        TNode* RightRotation(TNode* node);

    public:

        TNode* root = nullptr;
        TRedBlackTree() = default;

        TNode* Insert(TNode* node, TItem& data);
        TNode* Erase(TNode* node);
        TNode* Find(TNode* node, const std::string& key);
        
        TNode* EraseBalance(TNode* node);
        TNode* InsertBalance(TNode* node);

        static void Clear(TNode *node);
};

#endif
