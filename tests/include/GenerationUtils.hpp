#ifndef GENERATION_UTILS_HPP
#define GENERATION_UTILS_HPP

#include <string>
#include <vector>
#include <random>

std::string GenerateString(const std::vector<char>& alphabet, const uint strSize);
int GetRandomInt(int min, int max);

#endif

