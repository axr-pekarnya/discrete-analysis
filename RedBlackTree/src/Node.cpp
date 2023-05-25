#include "Node.hpp"

TNode::TNode(TNode* parentInput, TNode* leftInput, TNode* rightInput, bool colourInput, TItem& dataInput)
{
    this->parent = parentInput;
    this->left = leftInput;
    this->right = rightInput;
    this->colour = colourInput;
    this->data = dataInput;
}

TItem TNode::GetData() const {
    return this->data;
}

void TNode::SetData(const TItem& elem) {
    this->data = elem;
}
