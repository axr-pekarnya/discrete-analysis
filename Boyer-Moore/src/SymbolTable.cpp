#include "SymbolTable.hpp"

TSymbolTable::TSymbolTable(const std::vector<uint> &str) : strSize(str.size())
{
    for (int i = this->strSize - 1; i >= 0; --i) {
        this->body[str[i]].push_back(i);
    }
}

int TSymbolTable::Get(uint symbol, uint strIdx) const
{
    std::map< uint, std::vector<uint> >::const_iterator it = this->body.find(symbol);

    if (it == this->body.end()) {
        return this->strSize - strIdx;
    }

    const std::vector<uint>& vecIdx = it->second;
    
    for (uint i : vecIdx) 
    {
        if (i > strIdx){
            return 1;
        }
        else if (i < strIdx) {
            return strIdx - i;
        }
    }

    return this->strSize;
}

