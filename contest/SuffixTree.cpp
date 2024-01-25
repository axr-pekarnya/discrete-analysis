#include <bits/stdc++.h>

class TNode 
{
    friend class TSufTree;

    public:

        ~TNode() {
            for (std::pair <char, TNode *> node : this->edges) {
                delete node.second;
            }
        }

    private:

        TNode* link;

        int start;
        int idx = -1;
        
        std::shared_ptr<int> end;
        std::map <char, TNode* > edges;
};

class TSufTree 
{
    public:
        
        TSufTree(std::string& text, int size) 
        {
            data = text;
            firstSize = size;
            
            Init();
            SetIndex(root, 0);
        }

        std::pair<int, std::vector<std::string>> FindLCP()
        {
            std::vector<int> startIdx;
            Walk(root, 0, &curRes, startIdx);
            
            std::vector<std::string> result;
            std::string tmp;
            
            for (size_t i = 0; i < startIdx.size();++i) 
            {
                tmp.clear();

                for (int k = 0; k < curRes; k++) {
                    tmp += data[k + startIdx[i]];
                }

                result.push_back(tmp);
            }

            std::sort(result.begin(), result.end());

            return std::make_pair(this->curRes, result);
        }
       
        ~TSufTree() {
            delete root;
        }


    protected:
       
        std::string data;

        TNode* root = NULL;
        TNode* prevNode = NULL;
        TNode* curNode = NULL;

        int curEdge = -1;
        int curLen = 0;
        int curRes = 0; 
        
        int sufCnt = 0;
        
        std::shared_ptr<int> leafEnd = std::make_shared<int>(-1);
        
        int size = -1; 
        int firstSize = 0;

    private:

        TNode* AddNode(int start, std::shared_ptr<int> end) 
        {
            TNode* node = new class TNode();

            node->link = root;
            node->start = start;
            node->end = end;
        
            return node;
        }
        
        void Init()  
        {
            size = data.size();
            root = AddNode(-1, std::make_shared<int>(-1));
            curNode = root;
        
            for (int i = 0; i < size; i++) {
                Extend(i);
            }
        }
        
        int GetEdgeLen(TNode* n) 
        {
            if (n == root) {
                return 0;
            }
        
            return *(n->end) - (n->start) + 1;
        }

        
        int WalkDown(TNode* currTNode) 
        {
            if (curLen >= GetEdgeLen(currTNode)) 
            {
                curEdge += GetEdgeLen(currTNode);
                curLen -= GetEdgeLen(currTNode);
                curNode = currTNode;
            
                return 1;
            }

            return 0;
        }
        
        void Extend(int pos)
        {
            ++*leafEnd;
            sufCnt++;
            prevNode = NULL;

            while (sufCnt > 0) 
            {
                if (curLen == 0) {
                    curEdge = pos; 
                }

                if (!curNode->edges[data[curEdge]]) 
                {
                    curNode->edges[data[curEdge]] = AddNode(pos, leafEnd);
                 
                    if (prevNode != NULL) 
                    {
                        prevNode->link = curNode;
                        prevNode = NULL;
                    }
                }
                else 
                {
                    TNode* next = curNode->edges[data[curEdge]];
                
                    if (WalkDown(next)) {
                        continue;
                    }

                    if (data[next->start + curLen] == data[pos]) 
                    {
                        if (prevNode != NULL && curNode != root) 
                        {
                            prevNode->link = curNode;
                            prevNode = NULL;
                        }
                    
                        curLen++;
                        break;
                    }

                    int splitEnd = next->start + curLen - 1;
                    TNode* split = AddNode(next->start, std::make_shared<int>(splitEnd));
                    curNode->edges[data[curEdge]] = split;

                    split->edges[data[pos]] = AddNode(pos, leafEnd);
                    next->start += curLen;
                    split->edges[data[next->start]] = next;

                    if (prevNode != NULL) {
                        prevNode->link = split;
                    }

                    prevNode = split;
                }

                sufCnt--;

                if (curNode == root && curLen > 0) 
                {
                    curLen--;
                    curEdge = pos - sufCnt + 1;
                }
                else if (curNode != root) {
                    curNode = curNode->link;
                }
            }
        }
        
        void SetIndex(TNode* n, int curHeight) 
        {
            if (n == NULL)  {
                return;
            }

            int leaf = 1;
        
            for (auto child : n->edges) 
            {
                leaf = 0;
                SetIndex(child.second, curHeight + GetEdgeLen(child.second));
            }

            if (leaf == 1) {
                n->idx = size - curHeight;
            }
        }
        
        int Walk(TNode* node, int curHeight, int* maxHeight, std::vector<int>& startIdx) 
        {
            if (node == NULL) {
                return 0;
            }
            
            int ret = -1;
        
            if (node->idx < 0) 
            { 
                for (auto child : node->edges) 
                {
                    ret = Walk(child.second, curHeight + GetEdgeLen(child.second), maxHeight, startIdx);
                
                    if (node->idx == -1) {
                        node->idx = ret;
                    }
                    else if (
                                (node->idx == -2 && ret == -3) 
                                || (node->idx == -3 && ret == -2) 
                                || node->idx == -4 
                                || ret == -4
                            ) 
                    {
                        node->idx = -4;
                        
                        if (*maxHeight < curHeight) 
                        {
                            *maxHeight = curHeight;
                            
                            startIdx.clear();
                            startIdx.push_back(*(node->end) - curHeight + 1);
                        }
                        else if (
                            *maxHeight == curHeight 
                            && !startIdx.empty() 
                            && startIdx.back() != *(node->end) - curHeight + 1
                            ) {
                            startIdx.push_back(*(node->end) - curHeight + 1);
                        }
                    }
                }
            }
            else if (node->idx > -1 && node->idx < firstSize) { 
                return -2;
            }
            else if (node->idx >= firstSize) { 
                return -3;
            }

            return node->idx;
        }
};

int main() 
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::string first, second;
    std::cin >> first >> second;

    first += "#";
    second += "$";
    std::string data = first + second;

    TSufTree tree(data, first.size());
    std::pair<int, std::vector<std::string>> result = tree.FindLCP();
    
    std::cout << result.first << '\n';

    for (std::string& elem : result.second) {
        std::cout << elem << '\n';
    }

    return 0;
}