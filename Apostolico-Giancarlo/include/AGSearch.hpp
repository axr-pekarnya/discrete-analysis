#ifndef AG_SEARCH_HPP
#define AG_SEARCH_HPP

#include <vector>

#include "NFunction.hpp"
#include "LFunction.hpp"
#include "LsFunction.hpp"
#include "GoodSuffix.hpp"
#include "SymbolTable.hpp"
#include "SuccesfullShift.hpp"

std::vector<uint32_t> AGSearch(std::vector<uint32_t>& text, std::vector<uint32_t>& pattern);

#endif

