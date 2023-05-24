#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using pii = std::pair<uint32_t, uint32_t>;

std::ostream& operator<<(std::ostream &os, const std::vector<int> &vec)
{
    for (int elem : vec){
        os << elem << ' ';
    }
    os << '\n';

    return os;
}

std::vector<int> ZFunction(std::vector<uint32_t>& str);
std::vector<int> NFunction(std::vector<uint32_t>& str);
std::vector<int> LFunction(std::vector<int>& nFucntion);
std::vector<int> LsFunction(std::vector<int>& nFunction);

class TGoodSuffix
{
    public:
        TGoodSuffix(std::vector<int>& lFunctionInput, std::vector<int>& lsFunctionInput) : 
            lFunction(lFunctionInput), 
            lsFunction(lsFunctionInput),
            size(lFunction.size()) {}
    
        uint32_t Get(uint32_t idx)
        {
            if (!idx)
            {
                if (size > 2){
                    return size - lsFunction[1] - 1;
                }

                return 1;
            }

            if (idx == (uint32_t)this->size - 1){
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
        uint32_t size;
};

class TSymbolTable
{
    public:
        TSymbolTable(std::vector<uint32_t>& pattern){
            for (unsigned i = 0; i < pattern.size(); ++i){
                this->table[pattern[i]] = i;
            }
        }

        uint32_t Get(uint32_t symbol, uint32_t idx)
        {
            auto it = table.find(symbol);

            if (it == table.end()){
                return idx + 1;
            }

            return idx - it->second; 
        }

    private:
        std::map<uint32_t, uint32_t> table;
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

std::vector<uint32_t> ParsePattern() 
{
    std::vector<uint32_t> result;
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

std::vector<uint32_t> ParseText(std::vector<pii>& positions) 
{
    std::vector<uint32_t> result;
        
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

std::vector<int> NFunction(std::vector<uint32_t>& str)
{
    std::vector<uint32_t> strRev = str;
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
    std::vector<uint32_t> pattern = ParsePattern();
    std::vector<uint32_t> text = ParseText(positions);

    if (!text.size()){
        return 0;
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
                    std::cout << positions[j - pattern.size() + 1] << '\n';

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
                std::cout << positions[j - pattern.size() + 1] << '\n';

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
       
    return 0;
}


