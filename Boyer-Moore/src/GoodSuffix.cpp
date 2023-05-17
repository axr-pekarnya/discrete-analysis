#include "GoodSuffix.hpp"

TGoodSuffix::TGoodSuffix(std::vector<int>& lFunction) :
    body(lFunction), strSize(lFunction.size()) {}

int TGoodSuffix::Get(int strIdx) const
{
    if (strIdx >= this->strSize) {
        return 1;
    }

    if (this->body[strIdx] == 0) {
        return this->strSize - this->prefixSize;
    }

    return this->strSize - this->body[strIdx] - 1;
}

int TGoodSuffix::GetPrefixSize() const {
    return this->prefixSize;
}


