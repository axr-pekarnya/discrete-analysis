#include <bits/stdc++.h>

int INF = 2e9;

class IGraph
{
    public:
        int Size() {
            return this->data.size();
        }

        void SetVertex(int i, int j, int value) {
            this->data[i][j] = value;
        }

        int GetVertex(int i, int j) {
            return this->data[i][j];
        }

        bool Search(int source, int destination, std::vector<int> &parents);
    
    protected:
        std::vector<std::vector<int>> data;
};

class TGraph : public IGraph
{
    public:
        TGraph(int n) {
            this->data = std::vector<std::vector<int>>(n + 1, std::vector<int>(n + 1));
        }

        void SetVertex(int i, int j, int value) {
            this->data[i][j] = value;
        }

        int GetVertex(int i, int j) {
            return this->data[i][j];
        }

        bool Search(int source, int destination, std::vector<int> &parents)
        {
            std::vector<bool> visited(this->Size());
            std::queue<int> mem;

            mem.push(source);
            visited[source] = true;
            parents[source] = -1; 

            while (!mem.empty()) 
            {
                int lastVer = mem.front();
                mem.pop();
            
                for (int curVer = 0; curVer < this->Size(); ++curVer) 
                {
                    if (!visited[curVer] && this->data[lastVer][curVer]) 
                    {
                        mem.push(curVer);
                        parents[curVer] = lastVer;
                        visited[curVer] = true;
                        
                        if (curVer == destination) {
                            return true;
                        }
                    }
                }
            }

            return false;
        }
    };

int64_t GetMaxFlow(TGraph &graph, int source, int destination)
{
    int64_t result = 0;
    
    TGraph resGraph = graph;
    std::vector<int> parents(graph.Size());

    while (resGraph.Search(source, destination, parents)) 
    {
        int curFlow = INF;
    
        for (int curVertex = destination; curVertex != source; curVertex = parents[curVertex]) {
            curFlow = std::min(curFlow, graph.GetVertex(parents[curVertex], curVertex));
        }

        for (int curVertex = destination; curVertex != source; curVertex = parents[curVertex]) 
        {
            resGraph.SetVertex(parents[curVertex], curVertex, resGraph.GetVertex(parents[curVertex], curVertex) - curFlow);
            resGraph.SetVertex(curVertex, parents[curVertex], resGraph.GetVertex(curVertex, parents[curVertex]) + curFlow);
        }

        result += curFlow;
    }

    return result;
}

int main(void)
{
    int n, m;
    std::cin >> n >> m;

    TGraph graph(n);
   
    int src, dst, value;

    for (int i = 0; i < m; ++i) 
    {
        std::cin >> src >> dst >> value;
        graph.SetVertex(src, dst, value);
    }
    
    std::cout << GetMaxFlow(graph, 1, n) << '\n';
    
    return 0;
}
