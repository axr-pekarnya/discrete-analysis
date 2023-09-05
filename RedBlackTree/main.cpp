#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "Item.hpp"
#include "Node.hpp"
#include "RedBlackTree.hpp"
#include "Formatter.hpp"
#include "FileManager.hpp"

int main()
{
    std::ofstream fout;
    std::ifstream fin;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string strInput;
    std::string key;
    
    TRedBlackTree *tree = new TRedBlackTree();
    TFileManager* fileManager = new TFileManager();
    TItem data;
    
    while (std::cin >> strInput) 
    {
        if (!strInput.compare("+")) 
        {
            std::cin >> data;
            tree->Insert(tree->root, data);
        }
        else if (!strInput.compare("-")) 
        {
            std::cin >> key;
        
            TNode *need_to_delete = tree->Find(tree->root, key);
        
            if (need_to_delete == nullptr) {
                std::cout << "NoSuchWord\n";
            }
            else {
                tree->Erase(need_to_delete);
            }
        }
        else if (!strInput.compare("!")) 
        {
            std::cin >> strInput;

            if (!strInput.compare("Save")) 
            {
                std::cin >> strInput;

                fout.open(strInput,  std::ios::out | std::ios::binary | std::ios::trunc);

                fileManager->Save(tree->root, fout);
                
                fout.close();

                std::cout << "OK\n";
            }
            else if (!strInput.compare("Load")) 
            {
                std::cin >> strInput;
                
                fin.open(strInput, std::ios::in | std::ios::binary);
                
                tree->Clear(tree->root);
                tree->root = fileManager->Load(tree->root, fin);
                
                fin.close();

                std::cout << "OK\n";
            }
        }
        else 
        {
            TNode *found = tree->Find(tree->root, strInput);
        
            if (found == nullptr){
                std::cout << "NoSuchWord" << std::endl;
            }
            else { 
                std::cout << "OK: " << found->GetData().GetValue() << '\n';
            }
        }
    }

    delete fileManager;
    delete tree;
    
    return 0;
}
