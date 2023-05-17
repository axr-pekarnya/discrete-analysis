#include <iostream>

#include "ZFunction.hpp"

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string text;
    std::string pattern;

    std::cin >> text >> pattern;
    std::string sample = pattern + '#' + text;
    std::vector<int> res = Z_Function(sample);

    for (int i = 0; i < (int)res.size(); ++i){
        if (res[i] == (int)pattern.length()){
            std::cout << i - pattern.length() - 1 << '\n';
        }
    }

    return 0;
}


