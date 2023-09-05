#include <gtest/gtest.h>
#include <chrono>
#include "GenerationUtils.hpp"

#include <vector>
#include <string>

#include "AGSearch.hpp"

using pis = std::pair<int, std::string>;

TEST(AGTest, BenchmarkTest)
{
    double avg;
    std::chrono::steady_clock::time_point begin, end;

    for (int numOfItems = 128; numOfItems <= 65536; numOfItems *= 2)
    {
        std::vector<uint32_t> text;
        std::string strText;

        for (int i = 0; i < numOfItems; ++i)
        {
            text.push_back(GetRandomInt(0, 65536));
            strText += std::to_string(text[i]) + ' ';
        }

        int patternSize = GetRandomInt(1, 8);
        std::vector<uint32_t> pattern;
        std::string strPattern;

        int textPosition = GetRandomInt(0, numOfItems - 1);
        for (int i = 0; i < patternSize; ++i)
        {
            if (i > numOfItems - 1){
                break;
            }

            pattern.push_back(text[textPosition + i]);
            strPattern += std::to_string(text[textPosition + i]) + ' ';
        }

        std::vector<int> entries;

        begin = std::chrono::steady_clock::now();

        int idx = (int)strText.find(strPattern);
        while (idx != (int)std::string::npos)
        {
            entries.push_back(idx);
            idx = strText.find(strPattern, idx + 1);
        }

        end = std::chrono::steady_clock::now();
        avg = std::chrono::duration<double>(end - begin).count();

        std::vector<int> samples;

        for (auto& elem : entries)
        {
            std::string sample = std::string(strText.begin() + elem, strText.begin() + strText.find(' ', elem));
            samples.push_back(std::stoi(sample));
        }

        std::cout << "Searching of " << numOfItems << " elements by std::find : " << ((avg) * 1000) * 1000 << " us\n";
        
        auto begin = std::chrono::steady_clock::now();

        std::vector<uint32_t> AGEntries = AGSearch(text, pattern);

        auto end = std::chrono::steady_clock::now();
        avg = std::chrono::duration<double>(end - begin).count();

        std::cout << "Insertion of " << numOfItems << " elements to set: " << ((avg / numOfItems) * 1000) * 1000 << " us\n";
        std::cout << "---------------------------------------------------\n";

        EXPECT_EQ(AGEntries.size(), entries.size());

        for (int i = 0; i < (int)samples.size(); ++i){
            EXPECT_EQ(text[AGEntries[i]], samples[i]);
        }
    }
}
