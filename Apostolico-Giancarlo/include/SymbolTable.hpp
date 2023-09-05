#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <vector>
#include <string>
#include <map>

#include <iostream>

class TSymbolTable
{
    public:
        TSymbolTable(std::vector<uint32_t>& pattern);
        int Get(uint32_t symbol, int idx);

    private:
        std::map<uint32_t, uint32_t> table;
};

#endif

