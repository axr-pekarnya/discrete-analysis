#include "LFunction.hpp"

#include <iostream>

std::vector<int> LFunction(std::vector<int>& nFunction)
{
    std::vector<int> result(nFunction.size(), 0);

    for (int i = 0; i < (int)nFunction.size() - 1; ++i)
    {
        int idx = nFunction.size() - nFunction[i];
        
        if (idx < (int)nFunction.size()){
            result[idx] = i;
        }
    }

    return result;
}
