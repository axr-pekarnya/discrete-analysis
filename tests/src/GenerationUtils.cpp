#include "../include/GenerationUtils.hpp"

int GetRandomInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(mt);
}

std::string GenerateString(const std::vector<char>& alphabet, const uint strSize)
{
    std::string result;

    for (int i = 0; i < (int)strSize; ++i)
    {
        uint64_t idx = GetRandomInt(0, alphabet.size() - 1);
        char elem = alphabet[idx];
        result.push_back(elem);
    }

    return result;
}

