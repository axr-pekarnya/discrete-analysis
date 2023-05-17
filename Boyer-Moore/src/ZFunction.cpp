#include "ZFunction.hpp"

std::vector<int> ZFunction(std::string &str) 
{
    std::vector<int> result(str.length());
    int left = 0, right = 0;

    for(int i = 1; i < (int)str.length(); ++i) 
    {
        if(i < right){
            result[i] = std::min(right - i, result[i - left]);
        }

        while(str[result[i]] == str[i + result[i]]) {
            result[i]++;
        }

        if(i + result[i] > right) 
        {
            left = i;
            right = i + result[i];
        }
    }
    return result;
}


