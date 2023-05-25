#ifndef GOOD_SUFFIX_HPP
#define GOOD_SUFFIX_HPP

#include "LFunction.hpp"

#include <vector>
#include <string>

class TGoodSuffix
{
    public:
        TGoodSuffix(std::vector<int>& lFunctionInput, std::vector<int>& lsFunctionInput); 
        int Get(int idx);

    private:
        std::vector<int> lFunction;
        std::vector<int> lsFunction;
        uint32_t size;
};

#endif

