#ifndef GOOD_SUFFIX_HPP
#define GOOD_SUFFIX_HPP

#include "LFunction.hpp"

#include <vector>
#include <string>

#include <iostream>

class TGoodSuffix 
{
    public:
        TGoodSuffix(std::vector<int>& lFunction);
     
        int Get(int strIdx) const; 
        int GetPrefixSize() const;

        void DbOut()
        {
            for (int& it : body){
                std::cout << it << ' ';
            }
            std::cout << '\n';
        }
     
    private:
        std::vector<int> body;
        int strSize;
        int prefixSize = 0;
};

#endif

