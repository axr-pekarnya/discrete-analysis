#include <bits/chrono.h>
#include <gtest/gtest.h>
#include <chrono>
#include "GenerationUtils.hpp"

#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>

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

        std::cout << "Insertion of " << numOfItems << " elements to map: " << ((avg / numOfItems) * 1000) * 1000 << " us\n";
        
        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            set.insert(elem);

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();
        }

        std::cout << "Insertion of " << numOfItems << " elements to set: " << ((avg / numOfItems) * 1000) * 1000 << " us\n";

        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            tree->Insert(tree->root, elem);

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();
        }

        std::cout << "Insertion of " << numOfItems << " elements to tree: " << ((avg / numOfItems) * 1000) * 1000 << " us\n";
   

        std::cout << "-----------\n";


        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            map.find(elem.GetKey());

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();
        }

        std::cout << "Searching of " << numOfItems << " elements in map: " << ((avg / numOfItems) * 1000) * 1000 << " us\n";

        
        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            set.find(elem);

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();
        }

        std::cout << "Searching of " << numOfItems << " elements in set: " << ((avg / numOfItems) * 1000) * 1000 << " us\n";
 

        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            TNode* value = tree->Find(tree->root, elem.GetKey());

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();

            EXPECT_EQ(value->GetData().GetValue(), elem.GetValue());
        }

        std::cout << "Searching of " << numOfItems << " elements in tree: " << ((avg / numOfItems) * 1000) * 1000 << " us\n";


        std::cout << "-----------\n";


        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            map.erase(elem.GetKey());

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();
        }

        std::cout << "Erasing of " << numOfItems << " elements in map: " << ((avg / numOfItems) * 1000) * 1000 << " us\n";

        
        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            set.erase(elem);

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();
        }

        std::cout << "Erasing of " << numOfItems << " elements in set: " << ((avg / numOfItems) * 1000) * 1000 << " us\n";
 

        avg = 0;
        for (TItem& elem : items)
        {
            auto begin = std::chrono::steady_clock::now();

            tree->Erase(tree->Find(tree->root, elem.GetKey()));

            auto end = std::chrono::steady_clock::now();
            avg += std::chrono::duration<double>(end - begin).count();

            EXPECT_EQ(tree->Find(tree->root, elem.GetKey()), nullptr);
        }

        std::cout << "Erasing of " << numOfItems << " elements in tree: " << ((avg / numOfItems) * 1000) * 1000 << " us\n";

        std::cout << "---------------------------------------------------\n";
    }
}
