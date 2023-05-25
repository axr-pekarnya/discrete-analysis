#include "NFunction.hpp"

std::vector<int> NFunction(std::vector<uint32_t>& str)
{
    std::vector<uint32_t> strRev = str;
    std::reverse(strRev.begin(), strRev.end());
    
    std::vector<int> result = ZFunction(strRev);
    std::reverse(result.begin(), result.end());

    return result;
}

