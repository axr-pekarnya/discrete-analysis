#include <bits/stdc++.h>

class TSegment {
public:
    TSegment(int left, int right, int idx){
        this->left = left;
        this->right = right;
        this->idx = idx;
    }
    TSegment() = default;

    int GetLeft() const {
        return this->left;
    }

    int GetRight() const {
        return this->right;
    }

    int GetIdx() const {
        return this->idx;
    }

    void SetLeft(int value){
        this->left = value;
    }

    void SetRight(int value){
        this->right = value;
    }

    void SetIdx(int value){
        this->idx = value;
    }

private:
    int left;
    int right;
    int idx;

protected:

};

using psb = std::pair<std::vector<TSegment>, bool>;

bool operator<(TSegment const &seg1, TSegment const &seg2){
    return seg1.GetIdx() < seg2.GetIdx();
}

bool Select(std::vector<TSegment> &data, int m, std::vector<TSegment> &result) 
{
    TSegment curSegment(-1, -1, -1);

    for (TSegment &segment : data) {
        if (segment.GetRight() <= result.back().GetRight()) {
            continue;
        }

        if (segment.GetLeft() <= result.back().GetRight()) 
        {
            if (curSegment.GetRight() < segment.GetRight()) 
            {
                curSegment = segment;

                if (m <= curSegment.GetRight()) 
                {
                    result.push_back(curSegment);
                    return true;
                }
            }
        }
        else 
        {
            if (segment.GetLeft() <= curSegment.GetRight()) 
            {
                result.push_back(curSegment);
                curSegment = segment;

                if (m <= curSegment.GetRight())
                {
                    result.push_back(curSegment);
                    return true; 
                }
            }
            else {
                return false;
            }
        }
    }

    return false;
}

std::istream& operator >> (std::istream& in, std::vector<TSegment> &data) {
    for (int i = 0; i < (int)data.size(); ++i)
    {
        data[i].SetIdx(i);

        int left, right;
        in >> left >> right;

        data[i].SetLeft(left);
        data[i].SetRight(right);
    }

    return in;
}

bool Comparator(const TSegment &a, const TSegment &b) 
{
    int aLeft = a.GetLeft();
    int aRight = a.GetRight();
    int aIdx = a.GetIdx();

    int bLeft = b.GetLeft();
    int bRight = b.GetRight();
    int bIdx = b.GetIdx();

    return std::tie(aLeft, aRight, aIdx) < std::tie(bLeft, bRight, bIdx);
}

int main() 
{
    int n, m;
    std::cin >> n;

    std::vector<TSegment> data(n);
    
    std::cin >> data;
    std::cin >> m;

    std::sort(data.begin(), data.end(), Comparator);

    std::vector<TSegment> resData = {{-1, 0, -1}};
    bool found = Select(data, m, resData);
    
    std::sort(resData.begin(), resData.end());

    if (found) {
        std::cout << resData.size() - 1 << '\n';

        for (int i = 1; i < (int)resData.size(); ++i){
            std::cout << resData[i].GetLeft() << ' ' << resData[i].GetRight() << '\n';
        }
    } 
    else {
        std::cout << "0\n";
    }

    return 0;
}

