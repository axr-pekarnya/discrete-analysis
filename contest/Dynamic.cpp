#include <bits/stdc++.h>
#include <istream>
#include <vector>

std::istream& operator >> (std::istream& in, std::vector<std::vector<int64_t>> &data) {
    for (int64_t i = 0; i < (int64_t)data.size(); ++i){
        for (int64_t j = 0; j < (int64_t)data[0].size(); ++j){
            in >> data[i][j];
        }
    }

    return in;
}

void DisplayAnswer(std::vector<std::vector<int64_t>> &data)
{
    int64_t n = data.size();
    int64_t m = data[0].size(); 

    int64_t minValue = data[0][0];
    int64_t idx = 0;

    for (int64_t i = 1; i < m; ++i) {
        if (data[0][i] <= minValue) {
            minValue = data[0][i];
            idx = i;
        }
    }

    std::cout << minValue << '\n';

    int64_t i, j = idx;

    for (i = 0; i < n - 1; ++i) 
    {
        std::cout << '(' << i + 1 << "," << j + 1 << ") ";

        int64_t tmp;

        if (j == 0) {
            tmp = std::min(data[i + 1][j], data[i + 1][j + 1]);
        } 
        else if (j == m - 1) {
            tmp = std::min(data[i + 1][j - 1], data[i + 1][j]);
        }
        else {
            tmp = std::min({data[i + 1][j - 1], data[i + 1][j], data[i + 1][j + 1]});
        }

        if (tmp == data[i + 1][j + 1]) {
            j++;
        }
        else if (tmp == data[i + 1][j - 1]) {
            j--;
        }
    }

    std::cout << '(' << i + 1 << "," << j + 1 << ")\n";
}

int main() 
{
    int64_t n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int64_t>> data (n, std::vector<int64_t>(m));

    std::cin >> data;

/*
    for (int64_t i = 0; i < n; ++i) {
        for (int64_t j = 0; j < m; ++j) {
            std::cin >> data[i][j];
        }
    }
*/

    for (int64_t i = n - 2; i > -1; --i) {
        for (int64_t j = 0; j < m; ++j) 
        {
            if (j == 0) {
                data[i][j] += std::min(data[i + 1][j], data[i + 1][j + 1]);
            }
            else if (j == m - 1) {
                data[i][j] += std::min(data[i + 1][j - 1], data[i + 1][j]);
            } 
            else {
                data[i][j] += std::min({data[i + 1][j - 1], data[i + 1][j], data[i + 1][j + 1]});
            }
        }
    }

    DisplayAnswer(data);

    return 0;
}
