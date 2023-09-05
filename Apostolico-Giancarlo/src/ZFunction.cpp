#include "ZFunction.hpp"

std::vector<int> ZFunction(std::vector<uint32_t>& str) 
{
    std::vector<int> result(str.size());
    int left = 0, right = 0;

    for (int i = 1; i < (int)str.size(); ++i) 
    {
        if (i <= right){
            result[i] = std::min(right - i + 1, result[i - left]);
        }

        while (str[result[i]] == str[i + result[i]] && i + result[i] < (int)str.size()) {
            result[i]++;
        }

        if (i + result[i] - 1 > right)
        {
            left = i;
            right = i + result[i] - 1;
        }
    }

    return result;
}

