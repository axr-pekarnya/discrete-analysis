#include "GoodSuffix.hpp"

TGoodSuffix::TGoodSuffix(std::vector<int>& lFunctionInput, std::vector<int>& lsFunctionInput) : 
    lFunction(lFunctionInput), 
    lsFunction(lsFunctionInput),
    size(lFunction.size()) {}

int TGoodSuffix::Get(int idx)
{
    if (!idx)
    {
        if (size > 2){
            return size - lsFunction[1] - 1;
        }

        return 1;
    }

    if (idx == (int)this->size - 1){
        return 1;
    }

    if (lFunction[idx + 1]){
        return size - lFunction[idx + 1] - 1;  
    }

    return size - lsFunction[idx + 1]; 
}


