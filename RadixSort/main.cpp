#include "Number.hpp"
#include "RadixSort.hpp"

#include <fstream>

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

    std::ifstream fin("input.txt");

    while (fin >> first)
    {
        TNumber elem;
           
        fin >> second >> third;
        elem.key = first + second + third;

        fin >> value;
        elem.value = idx;

        values.push_back(value);
        ++idx;
        
        data.push_back(elem);
    }

    if (data.size()){
        RadixSort(data);
    }

    std::ofstream fout("output.txt");

    for (const TNumber & elem : data){
        fout << elem << '\t' << values[elem.value] << '\n';
    }

    fout.close();
    fin.close();

    return 0;
}


