#include "LsFunction.hpp"

std::vector<int> LsFunction(std::vector<int>& nFunction)
{
    std::vector<int> result(nFunction.size() + 1, 0);

    for (int i = nFunction.size() - 1; i >= 0; --i) 
    {
        int idx = (nFunction.size() - 1) - i;

        if (nFunction[idx - 1] == idx) {
            result[i] = idx;
        } 
        else {
            result[i] = result[i + 1];
        } 
    }

    return result;
}

