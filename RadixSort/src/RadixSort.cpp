#include "RadixSort.hpp"

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

        for (int i = 1; i < (int)count.size(); i++) {
            count[i] = count[i - 1] + count[i];
        }

        for (int i = (int)data.size() - 1; i >= 0; i--) 
        {
            char tmp = data[i].key[currentDigit];

            if (isalpha(tmp)) {
                res[--count[tmp - 'A']] = data[i];
            } 
            else if (isdigit(tmp)) {
                res[--count[tmp - '0']] = data[i];
            }
        }

        data = res;
    }
}
