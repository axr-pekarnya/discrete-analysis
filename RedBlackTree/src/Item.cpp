#include "Item.hpp"

std::string& TItem::GetKey() {
    return key;
}

uint64_t TItem::GetValue() const {
    return value;
}

void TItem::SetKey(std::string& keyInput){
    this->key = keyInput;
}

void TItem::SetValue(uint64_t valueInput){
    this->value = valueInput;
}

