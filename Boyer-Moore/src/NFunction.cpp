#include "NFunction.hpp"

std::vector<int> NFunction(std::vector<uint> str)
{
    std::reverse(str.begin(), str.end());
    
    std::vector<int> result = ZFunction(str);
    std::reverse(result.begin(), result.end());

    return result;
}
