#ifndef PARSING_UTILS_HPP
#define PARSING_UTILS_HPP

#include <vector>
#include <string>

using pii = std::pair<uint32_t, uint32_t>;

std::vector<uint32_t> ParsePattern(); 
std::vector<uint32_t> ParseText(std::vector<pii>& positions); 

#endif

