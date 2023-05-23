#include <iostream>

#include <ostream>
#include <vector>
#include <string>
#include <algorithm>

const int IDX_SHIFT = (int)'0';

struct TNumber
{
    std::string key;
    int value;
};

std::ostream& operator<<(std::ostream &strm, const TNumber &elem)
{
    strm << (char)(elem.key[0]) << ' ' \
        << (char)(elem.key[1]) \
        << (char)(elem.key[2]) \
        << (char)(elem.key[3]) << ' ' \
        << (char)(elem.key[4]) \
        << (char)(elem.key[5]);

    return strm;
}

void RadixSort(std::vector<TNumber> &data) 
{
    std::vector<TNumber> res(data.size());

    for (int currentDigit = 5; currentDigit >= 0; currentDigit--) 
    {
        std::vector<unsigned> count(26);

        for (auto &elem: data) 
        {
            char tmp = elem.key[currentDigit];
         
            if (isalpha(tmp)) {
                ++count[tmp - 'A'];
            }
            else if (isdigit(tmp)) {
                ++count[tmp - '0'];
            }
        }

        for (int i = 1; i < count.size(); i++) {
            count[i] = count[i - 1] + count[i];
        }

        for (int i = (int) data.size() - 1; i >= 0; i--) 
        {
            char tmp = data[i].key[currentDigit];
        
            if (isalpha(tmp)) {
                res[--count[tmp - 'A']] = data[i];
            } else if (isdigit(tmp)) {
                res[--count[tmp - '0']] = data[i];
            }
        }

        data = res;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::string inputStr;
    std::vector<TNumber> data;

    std::vector<std::string> values;
    int idx = 0;

    std::string first, second, third, value;

    while (std::cin >> first)
    {
        TNumber elem;
    
        std::cin >> second >> third;
        elem.key = first + second + third;

        std::cin >> value;
        elem.value = idx;

        values.push_back(value);
        ++idx;
        
        data.push_back(elem);
    }

    if (data.size()){
        RadixSort(data);
    }

    for (const TNumber & elem : data){
        std::cout << elem << '\t' << values[elem.value] << '\n';
    }

    return 0;
}



