#ifndef NODE_HPP
#define NODE_HPP

#include "Item.hpp"

class TNode 
{
    public:
        TNode* parent;
        TNode* left;
        TNode* right;
        bool colour;

        TNode(TNode* parentInput, TNode* leftInput, TNode* rightInput, bool colourInput, TItem& dataInput);
        
        TItem GetData() const;
        void SetData(const TItem& elem);

    private:
        TItem data;
};

#endif
