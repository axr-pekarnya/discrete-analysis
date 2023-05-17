#include <bits/stdc++.h>

std::vector<int> ZFunction(std::vector<uint32_t> &str); 
std::vector<int> NFunction(std::vector<uint32_t> str);
std::vector<int> LFunction(std::vector<int>& nFunction);

class TGoodSuffix 
{
    public:
        TGoodSuffix(std::vector<int>& lFunction) :
    body(lFunction), strSize(lFunction.size()) {}
     
        int Get(int strIdx) const
        {
            if (strIdx >= this->strSize) {
                return 1;
            }

            if (this->body[strIdx] == 0) {
                return this->strSize - this->prefixSize;
            }

            return this->strSize - this->body[strIdx] - 1;
        }

        int GetPrefixSize() const {
            return this->prefixSize;
        }

        void DbOut()
        {
            for (int& it : body){
                std::cout << it << ' ';
            }
            std::cout << '\n';
        }
     
    private:
        std::vector<int> body;
        int strSize;
        int prefixSize = 0;
};

class TSymbolTable 
{
    public:
        TSymbolTable(const std::vector<uint32_t> &str) : strSize(str.size())
        {
            for (int i = this->strSize - 1; i >= 0; --i) {
                this->body[str[i]].push_back(i);
            }
        }

        int Get(uint32_t symbol, uint32_t strIdx) const
        {
            std::map< uint32_t, std::vector<uint32_t> >::const_iterator it = this->body.find(symbol);

            if (it == this->body.end()) {
                return this->strSize - strIdx;
            }

            const std::vector<uint32_t>& vecIdx = it->second;
            
            for (uint32_t i : vecIdx) 
            {
                if (i > strIdx){
                    return 1;
                }
                else if (i < strIdx) {
                    return strIdx - i;
                }
            }

            return this->strSize;
        }
        
        void DbOut()
        {
            for (auto& it : this->body)
            {
                std::cout << it.first << ':';
            
                for (auto& num : it.second){
                    std::cout << num << ' ';
                }
                
                std::cout << '\n';
            }
        }
             
    private:
        std::map<uint32_t, std::vector<uint32_t>> body;
        int strSize;
};



std::vector<int> ZFunction(std::vector<uint32_t> &str) 
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

std::vector<int> NFunction(std::vector<uint32_t> str)
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
        result[idx] = i + 1;
    }

    return result;
}

using pii = std::pair<int, int>;

std::vector<uint32_t> ParseLine(bool parseOne, std::map<int, pii> &positions)
{
    std::vector<uint32_t> result;

    int numOfLine = 1, pos = 0;
    uint32_t num;
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
    std::vector<uint32_t> pattern = ParseLine(1, positions);
    std::vector<uint32_t> text = ParseLine(0, positions);

    std::vector<int> zFunction = ZFunction(pattern);
    std::vector<int> nFunction = NFunction(pattern);
    std::vector<int> lFunction = LFunction(nFunction);

    TSymbolTable symbolTable(pattern);
    TGoodSuffix goodSuffix(lFunction);

    for (uint32_t k = pattern.size() - 1; k < text.size();) 
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
