#include "RedBlackTree.hpp"

int TRedBlackTree::Compare(const std::string& str1, const std::string& str2)
{
    int len = std::min(str1.length(), str2.length());
    
    for(int i = 0; i < len; ++i)
    {
        if (std::tolower(str1[i]) > std::tolower(str2[i])){
            return 1;
        } 
        else if (std::tolower(str1[i]) < std::tolower(str2[i])){
            return -1;
        }
    }

    if (str1.length() > str2.length()){
        return 1;
    } 
    else if (str1.length() < str2.length()){
        return -1;
    } 
    else {
        return 0;
    }
}



TNode* TRedBlackTree::Left(TNode* node)
{
    if (node->left){
        return Left(node->left);
    }

    return node;
}

TNode* TRedBlackTree::Right(TNode* node)
{
    if (node->right){
        return Left(node->right);
    }
    
    return node;
}



TNode* TRedBlackTree::LeftRotation(TNode* node)
{
    TNode* parent = node->parent;
    TNode* cur = node;

    bool curColour = cur->colour;
    
    cur->colour = parent->colour;
    parent->colour = curColour;
    parent->right = cur->left;
    
    if (cur->left){
        cur->left->parent = parent;
    }

    cur->left = parent;
    cur->parent = parent->parent;
    
    if (parent->parent && parent->parent->left == parent) {
        parent->parent->left = cur;
    } 
    else if (parent->parent){
        parent->parent->right = cur;
    }

    parent->parent = cur;

    if (cur->parent == nullptr){
        root = cur;
    }
    
    return root;
}

TNode* TRedBlackTree::RightRotation(TNode* node)
{
    TNode* parent = node->parent;
    TNode* cur = node;

    bool curColour = cur->colour;

    cur->colour = parent->colour;
    parent->colour = curColour;
    parent->left = cur->right;
    
    if (cur->right){
        cur->right->parent = parent;
    }
    
    cur->right = parent;
    cur->parent = parent->parent;
    
    if (parent->parent && parent->parent->left == parent) {
        parent->parent->left = cur;
    }
    else if (parent->parent){
        parent->parent->right = cur;
    }
    
    parent->parent = cur;
    
    if (cur->parent == nullptr){
        root = cur;
    }
    
    return root;
}

TNode* TRedBlackTree::Insert(TNode* node, TItem& data)
{
    if (root == nullptr)
    {
        root = new TNode(nullptr, nullptr, nullptr, false, data);
//        std::cout << "OK" << std::endl;
    
        return root;
    }

    int next = Compare(data.GetKey(), node->GetData().GetKey());
    
    if (!next)
    {
//        std::cout << "Exist" << std::endl;

        return root;
    } 
    else if (next == 1)
    {
        if (node->right == nullptr)
        {
            node->right = new TNode(node, nullptr, nullptr, true, data);
//            std::cout << "OK" << std::endl;
        
            InsertBalance(node->right);
            return root;
        } 
        else {
            Insert(node->right, data);
        }
    } 
    else
    {
        if (node->left == nullptr)
        {
            node->left = new TNode(node, nullptr, nullptr, true, data);
//            std::cout << "OK" << std::endl;
        
            InsertBalance(node->left);
            return root;
        } 
        else {
            Insert(node->left, data);
        }
    }

    return root;
}



TNode* TRedBlackTree::Erase(TNode* node)
{
    if (!node->parent && !node->left && !node->right)
    {
        delete node;
//        std::cout << "OK" << std::endl;
        
        this->root = nullptr;
        return root;
    }

    TNode *replacement;
    
    if (node->colour)
    {
        if (!node->right && !node->left) 
        {
            if (node->parent) 
            {
                if (node->parent->left == node) {
                    node->parent->left = nullptr;
                }
                else {
                    node->parent->right = nullptr;
                }
            }

            delete node;
//            std::cout << "OK" << std::endl;
        
            return root;
        } 
        else if (node->right) 
        {
            replacement = Left(node->right);
            node->SetData(replacement->GetData());
        
            return Erase(replacement);
        } 
        else if (node->left) 
        {
            replacement = Right(node->left);
            node->SetData(replacement->GetData());
        
            return Erase(replacement);
        }
    } 
    else
    {
        if (node->left && node->left->colour && !node->right)
        {
            if (node->parent) 
            {
                if (node->parent->left == node) {
                    node->parent->left = node->left;
                }
                else {
                    node->parent->right = node->left;
                }
            }
            else {
                root = node->left;
            }
            
            node->left->colour = false;
            node->left->parent = node->parent;
            
            delete node;
            
//            std::cout << "OK" << std::endl;
            return root;
        } 
        else if (node->right && node->right->colour && !node->left)
        {
            if (node->parent) 
            {
                if (node->parent->left == node) {
                    node->parent->left = node->right;
                }
                else {
                    node->parent->right = node->right;
                }
            } 
            else {
                root = node->right;
            }
        
            node->right->colour = false;
            node->right->parent = node->parent;
        
            delete node;
        
//            std::cout << "OK" << std::endl;
            return root;
        }
        else if (!node->right && !node->left)
        {
            EraseBalance(node);
         
            if (node->parent) 
            {
                if (node->parent->left == node) {
                    node->parent->left = nullptr;
                }
                else {
                    node->parent->right = nullptr;
                }
            }
            
            delete node;
            
//            std::cout << "OK" << std::endl;
            return root;
        }
        else
        {
            if (node->right){
                replacement = Left(node->right);
            }
            else {
                replacement = Right(node->left);
            }

            node->SetData(replacement->GetData());

            Erase(replacement);
        }
    }

    return root;
}



TNode* TRedBlackTree::Find(TNode* node, const std::string& key)
{
    if (node == nullptr) {
        return nullptr;
    }

    int next = Compare(key, node->GetData().GetKey());
    
    if (!next){
        return node;
    }
    else if (next == 1){
        return Find(node->right, key);
    } 
    else {
        return Find(node->left, key);
    }
}



TNode* TRedBlackTree::EraseBalance(TNode* node)
{
    if (!node->parent){
        return root;
    }
    
    TNode* brother = node->parent->right;
    bool side = false;
    
    if (node->parent->right == node)
    {
        side = true;
        brother = node->parent->left;
    }

    if (brother == nullptr){
        return EraseBalance(node->parent);
    }
    if (brother->colour) 
    {
        if (side){
            RightRotation(brother);
        }
        else {
            LeftRotation(brother);
        }

        return EraseBalance(node);
    }
    else
    {
        if ((!brother->left || !brother->left->colour) && (!brother->right || !brother->right->colour))
        {
            brother->colour = true;
        
            if (brother->parent->colour)
            {
                brother->parent->colour = false;
                return root;
            } 
            else {
                return EraseBalance(brother->parent);
            }

        }
        if (side)
        {
            if ((!brother->left || !brother->left->colour) && brother->right->colour)
            {
                LeftRotation(brother->right);
                return EraseBalance(node);
            }
            
            brother->left->colour = false;
            return RightRotation(brother);
        } 
        else
        {
            if ((!brother->right || !brother->right->colour) && brother->left->colour)
            {
                RightRotation(brother->left);
                return EraseBalance(node);
            }
            
            brother->right->colour = false;
            return LeftRotation(brother);
        }
    }
}



TNode* TRedBlackTree::InsertBalance(TNode* node)
{
    if (!node->parent || !node->parent->colour) {
        return root;
    }
    
    if (node->parent->parent->left == node->parent)
    {
        if (node->parent->parent->right == nullptr || !node->parent->parent->right->colour) 
        {
            if (node->parent->right == node)
            {
                LeftRotation(node);
                RightRotation(node);
           
                return root;
            } 
            else
            {
                RightRotation(node->parent);
                return root;
            }
        }
        else if (node->parent->parent->right->colour) 
        {
            node->parent->colour = false;
            node->parent->parent->right->colour = false;
        
            if (node->parent->parent->parent != nullptr) {
                node->parent->parent->colour = true;
            }

            if (node->parent->parent->parent && node->parent->parent->parent->colour){
                return InsertBalance(node->parent->parent);
            }
        }
    } 
    else 
    {
        if (node->parent->parent->left == nullptr || !node->parent->parent->left->colour)
        {
            if (node->parent->left == node)
            {
                RightRotation(node);
                LeftRotation(node);
            
                return root;
            } 
            else 
            {
                LeftRotation(node->parent);
                return root;
            }
        }
        else if (node->parent->parent->left->colour) 
        {
            node->parent->colour = false;
            node->parent->parent->left->colour = false;
            
            if (node->parent->parent->parent != nullptr) {
                node->parent->parent->colour = true;
            }
            
            if(node->parent->parent->parent && node->parent->parent->parent->colour){
                return InsertBalance(node->parent->parent);
            }
        }
    }

    return root;
}



void TRedBlackTree::Clear(TNode *node)
{
    if (!node){
        return;
    }

    Clear(node->left);
    Clear(node->right);
    
    delete node;
}

