#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> Z_Function(std::string str) 
{
    std::vector<int> result(str.length());
    int left = 0, right = 0;

    for(int i = 1; i < (int)str.length(); ++i) 
    {
        if(i < right){
            result[i] = std::min(right - i, result[i - left]);
        }

        while(str[result[i]] == str[i + result[i]]) {
            result[i]++;
        }

        if(i + result[i] > right) 
        {
            left = i;
            right = i + result[i];
        }
    }
    return result;
}

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


