#include <iostream>

#include "LFunction.hpp"
#include "NFunction.hpp"
#include "PrefixFunction.hpp"

template<typename T>
std::vector<T> LLittleFunction(const std::string &s, std::vector<T> &v) {
    if (s.size() == 0) {
        return v;
    }
    //std::cout << s.size() << "\n";
    std::vector<T> l(s.size());
    for (int i = s.size() - 1; i >= 0; i--) {
        int j = (s.size() - 1) - i;
        if (v[j] == j + 1) {
            l[i] = j + 1;
        } else {
            if (i == (int)s.size() - 1) {
                l[i] = 0;
            } else {
                l[i] = l[i + 1];
            }
        }
    }
    
    return l;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int num;
    std::string pattern;
    std::string text;

    std::getline(std::cin, pattern);

    while (std::cin >> num) {
        text += std::to_string(num) + ' ';
    }

    std::vector<int> L = LFunction(pattern);
    std::vector<int> N = NFunction(pattern);
    std::vector<int> prefixFunction = PrefixFunction(pattern);

    std::vector<int> test = LLittleFunction(pattern, N);

    for (int elem : prefixFunction){
        std::cout << elem << ' ';
    }

    std::cout << '\n';

    for (int elem : test){
        std::cout << elem << ' ';
    }

    std::cout << '\n';
  

    return 0;
}
