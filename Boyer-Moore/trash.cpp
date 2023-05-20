#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using pii = std::pair<int, int>;

std::vector<int> ZFunction(std::vector<int> &str); 
std::vector<int> NFunction(std::vector<int> str);
std::vector<int> LFunction(std::vector<int>& nFunction);
std::vector<int> LsFunction(std::vector<int>& nFunction);



class TGoodSuffix 
{
    public:
        TGoodSuffix(std::vector<int>& nFunction) 
        {
            this->strSize = nFunction.size();
            this->lFunction = LFunction(nFunction);
            this->lsFunction = LsFunction(nFunction);
        }
     
        int Get(int strIdx)
        {
            if (strIdx == this->strSize) {
                return 1;
            }

            if (lFunction[strIdx] > 0){
                return strSize - this->lFunction[strIdx] - 1;
            }
            
            return strSize - this->lsFunction[strIdx];
        }

        int Shift(){
            return strSize - lsFunction[1];
        }

        void DbOut()
        {
            for (int& it : this->lFunction){
                std::cout << it << ' ';
            }
            std::cout << '\n';
        }
     
    private:
        std::vector<int> lFunction;
        std::vector<int> lsFunction;
        int strSize;
};

class TSymbolTable 
{
    public:
        TSymbolTable(const std::vector<int> &str) : strSize(str.size())
        {
            for (int i = 0; i < this->strSize; ++i) {
                this->body[str[i]] = i;
            }
        }

        int Get(int symbol, int strIdx)
        {
            std::map<int, int>::iterator it = this->body.find(symbol);

            if (it == this->body.end()) {
                return strIdx + 1;
            }

            //std::cout << strIdx << ' ' << this->body[symbol] << '\n';

            return strIdx - this->body[symbol];
        }
             
    private:
        std::map<int, int> body;
        int strSize;
};



std::vector<int> ZFunction(std::vector<int> &str) 
{
    std::vector<int> result(str.size());
    int left = 0, right = 0;

    for(int i = 1; i < (int)str.size(); ++i) 
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

std::vector<int> NFunction(std::vector<int> str)
{
    std::reverse(str.begin(), str.end());
    
    std::vector<int> result = ZFunction(str);
    std::reverse(result.begin(), result.end());

    return result;
}

std::vector<int> LFunction(std::vector<int> &nFunction)
{
    std::vector<int> result(nFunction.size(), 0);

    for (int i = 0; i < (int)nFunction.size() - 1; ++i)
    {
        int idx = nFunction.size() - nFunction[i];
        
        if (idx != (int)nFunction.size()){
            result[idx] = i;
        }
    }

    return result;
}

std::vector<int> LsFunction(std::vector<int> &nFunction)
{
    std::vector<int> result(nFunction.size(), 0);

    for (int i = nFunction.size() - 1; i >= 0; i--) 
    {
        int idx = (nFunction.size() - 1) - i;
        if (nFunction[idx] == idx + 1) {
            result[i] = idx + 1;
        } 
        else 
        {
            if (i == (int)nFunction.size() - 1) {
                result[i] = 0;
            } 
            else {
                result[i] = result[i + 1];
            }
        }
    }

    return result;
}


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

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::vector<pii> positions;
    std::vector<int> pattern = ParsePattern();
    std::vector<int> text = ParseText(positions);

    if (text.size() < pattern.size() || pattern.size() == 0){
        return 0;
    }
   
    //std::vector<int> pattern = ParseLine(1, positions);
    //std::vector<int> text = ParseLine(0, positions);

    std::vector<int> nFunction = NFunction(pattern);

    TSymbolTable symbolTable(pattern);
    TGoodSuffix goodSuffix(nFunction);

    for (int k = pattern.size() - 1; k < (int)text.size();) 
    {
        int i = k;
        bool found = true;

        for (int j = pattern.size() - 1; j >= 0; --j) 
        {
            if (text[i] != pattern[j]) 
            {
                int shiftSize = std::max(symbolTable.Get(text[i], j), goodSuffix.Get(j + 1));

                k += shiftSize;
                found = false;
                break;
            }

            --i;
        }
        
        if (found) 
        {
            pii it = positions[k - pattern.size() + 1];
            std::cout << it.first << ", " << it.second << '\n';

            k += goodSuffix.Shift();
        }
    }

/*
    int k = pattern.size() - 1;

    while (k < (int)text.size())
    {
        int tIdx = k;
        int pIdx = pattern.size() - 1;

        while (pIdx >= 0 && pattern[pIdx] == text[tIdx])
        {
            --pIdx;
            --tIdx;
        }

        if (pIdx == -1)
        {
            pii it = positions[k - pattern.size() + 1];
            std::cout << it.first << ", " << it.second << '\n';

            k += goodSuffix.Shift();
        }
        else {
            k += std::max(symbolTable.Get(text[tIdx], pIdx), goodSuffix.Get(pIdx + 1));
        }
    }
*/    
    return 0;
}

