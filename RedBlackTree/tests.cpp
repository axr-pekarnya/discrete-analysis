#include <gtest/gtest.h>
#include <chrono>

#include <vector>
#include <algorithm>

#include "GenerationUtils.hpp"

double GetAvgTime(const int numOfThreads)
{
    constexpr int runsCount = 10;
    double avg = 0;

    for(int i = 0; i < runsCount; ++i) 
    {
        std::vector<int> data = GenerateVector(8371);
        auto begin = std::chrono::high_resolution_clock::now();
        TimSort(data, numOfThreads);
        auto end = std::chrono::high_resolution_clock::now();
        avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    }

    return avg / runsCount;
}

TEST(RedBlackTreeTest, PerfomanceTest)
{
    std::vector<int> inputData = GenerateVector(2048);
    std::vector<int> checkData = inputData;
    const int numOfThreads = 1;

    std::stable_sort(checkData.begin(), checkData.end());

    ASSERT_TRUE(inputData.size() == checkData.size());

    for (int i = 0; i < (int)checkData.size(); ++i){
        EXPECT_EQ(inputData[i], checkData[i]);
    }
}

