#include "PrefixFunction.hpp"

#include <iostream>

std::vector<int> PrefixFunction(std::string &str)
{
    std::vector<int> N = NFunction(str);
    std::vector<int> result(N.size(), 0);

    for (int i = N.size() - 1; i > 0; --i)
    {
        int j = N.size() - i - 1;

        if (N[j] == j + 1){
            result[i] = N[j];
        }
        else 
        {
            if (i == (int)N.size() - 1) {
                result[i] = 0;
            }
            else 
            {
                result[i] = result[i + 1];
            }
        }
         
    }

    return result;
}

