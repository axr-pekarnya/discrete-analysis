#include "Formatter.hpp"

TFormatter::TFormatter()
{
    this->colour = NULL_COLOUR;
    this->value = 0;
    this->key = '0';
}

TFormatter::TFormatter(char colourInput, uint64_t valueInput, std::string& keyInput)
{
    if (colourInput){
        this->colour = RED_COLOUR;
    }
    else {
        this->colour = BLACK_COLOUR;
    }

    this->value = valueInput;
    this->key = keyInput;
}


