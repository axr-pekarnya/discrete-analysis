#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using pii = std::pair<int, int>;

std::ostream& operator<<(std::ostream &os, const std::vector<int> &vec)
{
    for (int elem : vec){
        os << elem << ' ';
    }
    os << '\n';

    return os;
}

std::vector<int> ZFunction(std::vector<int>& str);
std::vector<int> NFunction(std::vector<int>& str);
std::vector<int> LFunction(std::vector<int>& nFucntion);
std::vector<int> LsFunction(std::vector<int>& nFunction);

class TGoodSuffix
{
    public:
        TGoodSuffix(std::vector<int>& lFunctionInput, std::vector<int>& lsFunctionInput) : 
            lFunction(lFunctionInput), 
            lsFunction(lsFunctionInput),
            size(lFunction.size()) {}
    
        int Get(int idx)
        {
            if (!idx)
            {
                if (size > 2){
                    return size - lsFunction[1] - 1;
                }

                return 1;
            }

            if (idx == (int)this->size - 1){
                return 1;
            }

            if (lFunction[idx + 1]){
                return size - lFunction[idx + 1] - 1;  
            }

            return size - lsFunction[idx + 1]; 
        }

    private:
        std::vector<int> lFunction;
        std::vector<int> lsFunction;
        int size;
};

class TSymbolTable
{
    public:
        TSymbolTable(std::vector<int>& pattern){
            for (unsigned i = 0; i < pattern.size(); ++i){
                this->table[pattern[i]] = i;
            }
        }

        int Get(int symbol, int idx)
        {
            auto it = table.find(symbol);

            if (it == table.end()){
                return idx + 1;
            }

            return idx - it->second; 
        }

    private:
        std::map<int, int> table;
};

class TSuccesfulShift
{
    public:
        TSuccesfulShift(std::vector<int>& lsFunctionInput) :
            lsFunction(lsFunctionInput),
            size(lsFunctionInput.size() - 1) {}

        int Get()
        {
            if (this->size > 2){
                return size - lsFunction[1] - 1;
            }

            return 1;
        }
    
    private:
        std::vector<int> lsFunction;
        int size;
};

std::vector<int> ParsePattern() 
{
    std::vector<int> result;
    std::string buffer;
    char symbol = ' ';

    while (true) 
    {
        symbol = getchar();

        if (buffer.length() && symbol == ' ') 
        {
            result.push_back(std::stoul(buffer));
            buffer.clear();
        }
        else if (symbol == '\n')
        {
            if(buffer.length())
            {
                result.push_back(std::stoul(buffer));
                buffer.clear();
            }

            break;
        }
        else if (symbol >= '0' && symbol <= '9') {
            buffer.push_back(symbol);
        }
    }

    return result;
}

std::vector<int> ParseText(std::vector<pii>& positions) 
{
    std::vector<int> result;
        
    std::string buffer;
    char symbol = ' ';
  
    unsigned int numOfLine = 1;
    unsigned int posInLine = 0;

    while (true) 
    {
        symbol = getchar();

        if (buffer.length() && symbol == ' ') 
        {
            posInLine++;
            positions.emplace_back(numOfLine, posInLine);
            result.push_back(std::stoul(buffer));
            buffer.clear();
        }
        else if (symbol == '\n')
        {
            if(buffer.length())
            {
                posInLine++;
                positions.emplace_back(numOfLine, posInLine);
                result.push_back(std::stoul(buffer));
                buffer.clear();
            }

            posInLine = 0;
            numOfLine++;
        }
        else if (symbol == EOF)
        {
            if(buffer.length() != 0)
            {
                posInLine++;
                positions.emplace_back(numOfLine, posInLine);
                result.push_back(std::stoul(buffer));
            }

        break;
        }

        else if (symbol >= '0' && symbol <= '9') {
            buffer.push_back(symbol);
        }
    }

    return result;
}

std::vector<int> ZFunction(std::vector<uint>& str) 
{
    std::vector<int> result(str.size());
    int left = 0, right = 0;

    for (int i = 1; i < (int)str.size(); ++i) 
    {
        if (i <= right){
            result[i] = std::min(right - i + 1, result[i - left]);
        }

        while (str[result[i]] == str[i + result[i]] && i + result[i] < (int)str.size()) {
            result[i]++;
        }

        if (i + result[i] - 1 > right)
        {
            left = i;
            right = i + result[i] - 1;
        }
    }

    return result;
}

std::vector<int> NFunction(std::vector<int>& str)
{
    std::vector<int> strRev = str;
    std::reverse(strRev.begin(), strRev.end());
    
    std::vector<int> result = ZFunction(strRev);
    std::reverse(result.begin(), result.end());

    return result;
}

std::vector<int> LFunction(std::vector<int>& nFunction)
{
    std::vector<int> result(nFunction.size(), 0);

    for (int i = 0; i < (int)nFunction.size() - 1; ++i)
    {
        int idx = nFunction.size() - nFunction[i];
        
        if (idx < (int)nFunction.size()){
            result[idx] = i;
        }
    }

    return result;
}

std::vector<int> LsFunction(std::vector<int>& nFunction)
{
    std::vector<int> result(nFunction.size() + 1, 0);

    for (int i = nFunction.size() - 1; i >= 0; --i) 
    {
        int idx = (nFunction.size() - 1) - i;

        if (nFunction[idx - 1] == idx) {
            result[i] = idx;
        } 
        else {
            result[i] = result[i + 1];
        } 
    }

    return result;
}

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
    std::vector<int> pattern = ParsePattern();
    std::vector<int> text = ParseText(positions);

    if (!text.size()){
        return 0;
    }

    std::vector<int> nFunction = NFunction(pattern);
    std::vector<int> lFunction = LFunction(nFunction);
    std::vector<int> lsFunction = LsFunction(nFunction);

    TSymbolTable symbolTable(pattern);
    TGoodSuffix goodSuffix(lFunction, lsFunction);
    TSuccesfulShift succesShift(lsFunction);

    for (int k = pattern.size() - 1; k < (int)text.size();) 
    {
        int i = k;
        int j = pattern.size() - 1;

        while (j >= 0 && pattern[j] == text[i])
        {
            --i;
            --j;
        }
        
        if (j == -1) 
        {
            pii it = positions[k - pattern.size() + 1];
            std::cout << it.first << ", " << it.second << '\n';

            k += pattern.size() - lsFunction[1];
        }
        else {
            k += std::max(symbolTable.Get(text[i], j), goodSuffix.Get(j));
        }
    }
       
    return 0;
}


