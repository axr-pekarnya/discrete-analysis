#include "SymbolTable.hpp"

TSymbolTable::TSymbolTable(std::vector<uint32_t>& pattern){
    for (unsigned i = 0; i < pattern.size(); ++i){
        this->table[pattern[i]] = i;
    }
}

int TSymbolTable::Get(uint32_t symbol, int idx)
{
    auto it = table.find(symbol);

    if (it == table.end()){
        return idx + 1;
    }

    return idx - it->second; 
}

