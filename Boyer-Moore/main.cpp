#include <fstream>
#include <iostream>
#include <sstream>

#include "LFunction.hpp"
#include "NFunction.hpp"
#include "ZFunction.hpp"
#include "GoodSuffix.hpp"
#include "SymbolTable.hpp"

using pii = std::pair<int, int>;

std::vector<uint> ParseLine(bool parseOne, std::map<int, pii> &positions)
{
    std::vector<uint> result;

    int numOfLine = 1, pos = 0;
    uint num;
    std::string line;
    std::stringstream lineStrm;
    
    while (std::getline(std::cin, line))
    {
        int posInLine = 1;

        lineStrm.clear();
        lineStrm << line;

        while (lineStrm >> num)
        {
            result.push_back(num);

            if (!parseOne){
                if (posInLine) {
                    positions.insert({pos, {numOfLine, posInLine}});
                }
            }

            ++posInLine;
            ++pos;
        }

        if (parseOne){
            break;
        }

        ++numOfLine;
    }

    return result;
}

std::ostream& operator<<(std::ostream &os, const std::vector<int> &vec)
{
    for (int elem : vec){
        os << elem << ' ';
    }
    os << '\n';

    return os;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::map<int, pii> positions;
    std::vector<uint> pattern = ParseLine(1, positions);
    std::vector<uint> text = ParseLine(0, positions);

    std::vector<int> zFunction = ZFunction(pattern);
    std::vector<int> nFunction = NFunction(pattern);
    std::vector<int> lFunction = LFunction(nFunction);

    TSymbolTable symbolTable(pattern);
    TGoodSuffix goodSuffix(lFunction);

    for (uint k = pattern.size() - 1; k < text.size();) 
    {
		int i = (int)k;
		bool found = true;

		for (int j = pattern.size() - 1; j >= 0; --j) 
        {
			if (text[i] != pattern[j]) 
            {
				int shiftSize = std::max((int)symbolTable.Get(text[i], j), (int)goodSuffix.Get(j + 1));

				k += shiftSize;
				found = false;
				break;
			}

			--i;
		}
		
        if (found) 
        {
            std::map<int, pii>::iterator it = positions.find(k - pattern.size() + 1);

            std::cout << it->second.first << ", " << it->second.second << '\n';
		
            k += pattern.size() - goodSuffix.GetPrefixSize();
        }
	}
    
    return 0;
}
