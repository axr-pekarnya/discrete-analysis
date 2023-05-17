#include "NFunction.hpp"
#include "ZFunction.hpp"

std::vector<int> NFunction(std::string str)
{
    std::reverse(str.begin(), str.end());
    
    std::vector<int> result = ZFunction(str);
    std::reverse(result.begin(), result.end());

    return result;
}
