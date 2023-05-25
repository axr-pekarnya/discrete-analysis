#include "FileManager.hpp"

void TFileManager::Save(TNode* node, std::ofstream &fout)
{
    if (node)
    {
        TFormatter itemOutput(node->colour, node->GetData().GetValue(), node->GetData().GetKey());
        fout << itemOutput;

        Save(node->left, fout);
        Save(node->right, fout);
    }
    else 
    {
        TFormatter itemOutput;
        fout << itemOutput;
    }
}

TNode* TFileManager::Load(TNode *node, std::ifstream &fin)
{
    TFormatter itemInput;
    TItem data;

    fin >> itemInput;

    if (itemInput.colour != NULL_COLOUR)
    {
        data.SetKey(itemInput.key);
        data.SetValue(itemInput.value);
     
        if (itemInput.colour == RED_COLOUR){
            node = new TNode(nullptr, nullptr, nullptr, true, data);
        } 
        else {
            node = new TNode(nullptr, nullptr, nullptr, false, data);
        }
    
        node->left = Load(node->left, fin);
    
        if (node->left){
            node->left->parent = node;
        }

        node->right = Load(node->right, fin);
    
        if (node->right){
            node->right->parent = node;
        }

        return node;
    }

    return nullptr;
}

