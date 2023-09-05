#include "AGSearch.hpp"

#include <vector>

std::vector<uint32_t> AGSearch(std::vector<uint32_t>& text, std::vector<uint32_t>& pattern)
{
    std::vector<uint32_t> result;
    
    if (!text.size()){
        return result;
    }

    std::vector<int> nFunction = NFunction(pattern);
    std::vector<int> lFunction = LFunction(nFunction);
    std::vector<int> lsFunction = LsFunction(nFunction);

    TSymbolTable symbolTable(pattern);
    TGoodSuffix goodSuffix(lFunction, lsFunction);
    TSuccesfulShift succesShift(lsFunction);

    std::vector<int> m(text.size(), 0);

    for (uint32_t j = pattern.size() - 1; j < (uint32_t)text.size();)
    {
        int h = j;
        int i = pattern.size() - 1;

        while (true)
        {
            if (!m[h])
            {
                if (text[h] == pattern[i] && i == 0)
                {
                    result.push_back(j - pattern.size() + 1);

                    m[j] = pattern.size();
                    j += succesShift.Get();

                    break;
                }
                
                if (text[h] == pattern[i] && i > 0)
                {
                    --i;
                    --h;

                    continue;
                }
                
                if (text[h] != pattern[i])
                {
                    m[j] = j - h;

                    j += std::max(goodSuffix.Get(i), symbolTable.Get(text[h], i));
                    
                    break;
                }
            }
             
            if (m[h] < nFunction[i])
            {
                i -= m[h];
                h -= m[h];

                continue;
            }

            if (m[h] >= nFunction[i] && nFunction[i] >= i)
            {
                result.push_back(j - pattern.size() + 1);

                m[j] = j - h;
                j += succesShift.Get();
                
                break;
            }

            if (m[h] > nFunction[i] && nFunction[i] < i)
            {
                m[j] = j - h;
                j += std::max(goodSuffix.Get(i - nFunction[i]), symbolTable.Get(text[h - nFunction[i]], i - nFunction[i]));

                break;
            }

            if (m[h] == nFunction[i] && nFunction[i] > 0 && nFunction[i] < (int)i)
            {
                i -= m[h];
                h -= m[h];

                continue;
            }
        }
    }

    return result;
}

