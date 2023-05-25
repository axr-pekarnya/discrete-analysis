#include <bits/chrono.h>
#include <gtest/gtest.h>
#include <chrono>
#include "GenerationUtils.hpp"

#include <utility>
#include <vector>
#include <string>
#include <algorithm>

#include "Item.hpp"
#include "RedBlackTree.hpp"

using pis = std::pair<int, std::string>;

bool operator<(const TItem& elem1, const TItem& elem2)
{
    TItem elem3 = elem1;
    TItem elem4 = elem2;

    return elem3.GetKey() < elem4.GetKey();
}

TEST(RBTreeTest, BenchmarkTest)
{
    std::vector<char> alphabet;

    for (int i = 97; i <= 122; ++i){
        alphabet.push_back((char)i);
    }

    std::map<std::string, int> map;
    std::set<TItem> set;
    
    TRedBlackTree* tree = new TRedBlackTree();
    std::vector<TItem> items;

    double avg = 0;

    for (int numOfItems = 16; numOfItems <= 256; numOfItems *= 4)
    {
        for (int i = 0; i < numOfItems; ++i)
        {
            TItem data;
            std::string str = GenerateString(alphabet, numOfItems);
            data.SetKey(str);
            data.SetValue(GetRandomInt(-1023, 1024));

            items.emplace_back(data);
        }

        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            map[elem.GetKey()] = elem.GetValue();

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();
        }

        std::cout << "Insertion of " << numOfItems << " elements to map: " << avg / numOfItems << '\n';

        
        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            set.insert(elem);

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();
        }

        std::cout << "Insertion of " << numOfItems << " elements to set: " << avg / numOfItems << '\n';
 

        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            tree->Insert(tree->root, elem);

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();
        }

        std::cout << "Insertion of " << numOfItems << " elements to tree: " << avg / numOfItems << '\n';
    }
}
