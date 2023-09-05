#ifndef SUCCESFULL_SHIFT_HPP
#define SUCCESFULL_SHIFT_HPP

#include <vector>

#include "LsFunction.hpp"

class TSuccesfulShift
{
    public:
        TSuccesfulShift(std::vector<int>& lsFunctionInput);
        int Get();
    
    private:
        std::vector<int> lsFunction;
        int size;
};


#endif

