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
        TSymbolTable(const std::vector<int> &str)
        {
            this->strSize = str.size();

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

    std::vector<int> nFunction = NFunction(pattern);
    std::vector<int> m (text.size(), -1);

    TSymbolTable symbolTable(pattern);
    TGoodSuffix goodSuffix(nFunction);

    /*
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
    */

    for (int j = pattern.size() - 1; j < (int)text.size();)
    {
        int i = pattern.size() - 1;    
        int h = j;

        while (true) 
        {
            if (m[h] == 0) 
            {
                if (text[h] == pattern[i])
                {
                    if (i == 0) 
                    {
                        int entry_position = k - pattern.size() + 1;
                        entries.emplace_back(text[entry_position].str_number, text[entry_position].position); // сообщить о вхождении
                        m[j] = pattern.size(); // подстрока [k - pattern.size() + 1 .. k] совпадает с образцом
                        // такой сдвиг, что префикс образца должен совпасть с суффиксом
                        if (pattern.size() > 2) {
                            j += pattern.size() - little_l_function[1];
                        } else {
                            j++;
                        }
                        break; //конец фазы
                    } 
                    else 
                    { // если  i > 0
                        h--;
                        i--;
                    }
                } 
                else 
                { // несовпадение
                    m[j] = j - h;
                    // нахождение хорошего суффикса
                    int maxSuff = GoodSuffix(pattern, i, big_l_function, little_l_function);
                    // нахождение плохого символа
                    int maxSymb = BadSymbol(text[h] ,i, r_function);
                    j += std::max(maxSuff, maxSymb);
               
                    break; // конец фазы
                }
            } 
            else if (m[h] < nFunction[i]) {
                i -= m[h];
            } 
            else if (m[h] >= nFunction[i] && nFunction[i] >= i) 
            {
                int entry_position = j - pattern.size() + 1;
                entries.emplace_back(text[entry_position].str_number, text[entry_position].position); // сообщить о вхождении
                m[k] = j - h;
                // такой сдвиг, что префикс образца должен совпасть с суффиксом
                if (pattern.size() > 2) {
                    j += pattern.size() - little_l_function[1];
                } 
                else {
                    ++j;
                }

                break; // конец фазы
            } 
            else if (m[h] > nFunction[i] && nFunction[i] < i) 
            {
                m[j] = j - h;
                // несовпадение в i - n[i]
                // нахождение хорошего суффикса
                int pattern_pos = i - nFunction[i];
                unsigned text_symbol = text[h - nFunction[i]];
                int maxSuff = GoodSuffix(pattern, pattern_pos, big_l_function, little_l_function);
                int maxSymb = BadSymbol(text_symbol, pattern_pos, r_function);
                j += std::max(maxSuff, maxSymb);
                break; // конец фазы
            } 
            else if (m[h] == nFunction[i] && nFunction[i] < i) 
            {
                i -= m[h];
                h -= m[h];
            }
        }

        /*
        while (true)
        {
            if (m[h] == -1 || (nFunction[i] == 0 && m[h] == 0))
            {
                if (text[h] == pattern[i] && i == 1)
                {
                    std::cout << "Entry\n";

                    m[j] = pattern.size() - 1;
                    j += goodSuffix.Shift();
                }
                
                if (text[h] == pattern[i] && i > 1)
                {
                    --h;
                    --i;

                    continue;
                }

                if (text[h] != pattern[i])
                {
                    m[j] = j - h;
                    j += std::max(symbolTable.Get(text[h], i), goodSuffix.Get(i + 1));

                    break;
                }

            }

            if (m[h] < nFunction[i])
            {
                std::cout << "Entry\n";

                i = i - m[h];
                h = h - m[h];
               
                continue;
            }

            if (m[h] >= nFunction[i] && nFunction[i] == i && i > 0)
            {
                std::cout << "Entry\n";

                m[j] = j - h;
                j += goodSuffix.Shift();
            
                break;
            }

            if (m[h] > nFunction[i] && nFunction[i] < i)
            {
                m[j] = j - h;
                j += std::max(symbolTable.Get(text[h], i - nFunction[i]), goodSuffix.Get(i - nFunction[i] + 1));
            }

            if (m[h] == nFunction[i] && nFunction[i] > 0 && nFunction[i] < i)
            {
                i -= m[h];
                h -= m[h];
            }
        }
        */
    }

    return 0;
}

