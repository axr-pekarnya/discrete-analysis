#include <iostream>
#include <vector>

#include "AGSearch.hpp"
#include "ParsingUtils.hpp"

std::ostream& operator<<(std::ostream& fout, pii elem)
{
    fout << elem.first << ", " << elem.second;
    return fout;
}


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<pii> positions;
    std::vector<uint32_t> pattern = ParsePattern();
    std::vector<uint32_t> text = ParseText(positions);

    std::vector<uint32_t> result = AGSearch(text, pattern);

    for (auto& elem : result){
        std::cout << elem << ' ';
    }
    std::cout << '\n';

    return 0;
}


