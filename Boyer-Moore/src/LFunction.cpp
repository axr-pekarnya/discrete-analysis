#include "LFunction.hpp"

#include <iostream>

std::vector<int> LFunction(std::string &str)
{
    std::vector<int> N = NFunction(str);
    std::vector<int> result(N.size(), 0);

    for (int i = 0; i < (int)N.size() - 1; ++i)
    {
        int idx = N.size() - N[i];
        result[idx] = i + 1;
    }

    return result;
}

