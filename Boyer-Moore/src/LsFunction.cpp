#include "LsFunction.hpp"

std::vector<int> LsFunction(std::vector<int> &nFunction)
{
    std::vector<int> result(nFunction.size(), 0);

    for (int i = nFunction.size() - 1; i > 0; --i)
    {
        int j = nFunction.size() - i - 1;

        if (nFunction[j] == j + 1){
            result[i] = nFunction[j];
        }
        else 
        {
            if (i == (int)nFunction.size() - 1) {
                result[i] = 0;
            }
            else {
                result[i] = result[i + 1];
            }
        }
         
    }

    return result;
}

