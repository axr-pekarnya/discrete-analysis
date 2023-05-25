#include "SuccesfullShift.hpp"

TSuccesfulShift::TSuccesfulShift(std::vector<int>& lsFunctionInput) :
    lsFunction(lsFunctionInput),
    size(lsFunctionInput.size() - 1) {}

int TSuccesfulShift::Get()
{
    if (this->size > 2){
        return size - lsFunction[1] - 1;
    }

    return 1;
}

