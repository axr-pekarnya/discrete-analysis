#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <vector>
#include <string>
#include <map>

#include <iostream>

class TSymbolTable 
{
    public:
        TSymbolTable(const std::vector<uint>& str);
 
        int Get(uint symbol, uint strIdx) const;
        
        void DbOut()
        {
            for (auto& it : this->body)
            {
                std::cout << it.first << ':';
            
                for (auto& num : it.second){
                    std::cout << num << ' ';
                }
                
                std::cout << '\n';
            }
        }
             
    private:
        std::map<uint, std::vector<uint>> body;
        int strSize;
};

#endif

