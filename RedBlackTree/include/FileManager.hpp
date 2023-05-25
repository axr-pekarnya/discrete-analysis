#ifndef FILE_MANAGER_HPP
#define FILE_MANAGER_HPP

#include <fstream>
#include "Formatter.hpp"
#include "Node.hpp"

class TFileManager
{
    public:
        TFileManager() = default;
        
        static void Save(TNode* node, std::ofstream &fout);
        static TNode* Load(TNode *node, std::ifstream &fin);
};

#endif

