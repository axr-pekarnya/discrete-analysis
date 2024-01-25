#include <bits/stdc++.h>

bool Search(std::vector<std::vector<int > > &graph, int src, int dst, std::vector<int> &parent, std::vector<bool> visited) 
{
    std::queue <int> mem;
    mem.push(src);

    visited[src] = true;
    parent[src] = -1;

    while (!mem.empty()) 
    {
        int lastVer = mem.front();
        mem.pop();

        for (int curVer = 0; curVer < dst + 1; ++curVer) 
        {
            if (!visited[curVer] && graph[lastVer][curVer]) 
            {
                mem.push(curVer);
                parent[curVer] = lastVer;
                visited[curVer] = true;
            }
        }
    }

    return (visited[dst]);
}

int64_t GetMaxFlow(std::vector<std::vector<int > > &graph, int src, int dst) 
{
    std::vector<std::vector<int > > tmpGraph;

    tmpGraph.resize(dst + 1);

    for (int edge = 0; edge < dst + 1; ++edge) 
    {
        tmpGraph[edge].resize(dst + 1);
    
        for (int vertex = 0; vertex < dst + 1; ++vertex) {
            tmpGraph[edge][vertex] = graph[edge][vertex];
        }
    }

    std::vector<int> parent(dst + 1);
    std::vector<bool> visited(dst + 1);

    int64_t result = 0;

    while (Search(tmpGraph, src, dst, parent, visited)) 
    {
        int curFlow = INT_MAX;
    
        for (int vertex = dst; vertex != src; vertex = parent[vertex]) 
        {
            int prev = parent[vertex];
            curFlow = std::min(curFlow, tmpGraph[prev][vertex]);
        }

        for (int vertex = dst; vertex != src; vertex = parent[vertex]) 
        {
            int prev = parent[vertex];
            tmpGraph[prev][vertex] -= curFlow;
            tmpGraph[vertex][prev] += curFlow;
        }

        result += curFlow;
    }

    return result;
}

int main() {
    int ver, edg;
    std::cin >> ver >> edg;

    std::vector<std::vector<int >> graph;
    graph.resize(ver+1);
    
    for (int i = 0; i < ver + 1; ++i) {
        graph[i].resize(ver + 1);
    }

    int from, to, val;
    
    for (int j = 0; j < edg; ++j) 
    {
        std::cin >> from >> to >> val;
        graph[from][to] = val;
    }

    std::cout << GetMaxFlow(graph, 1, ver) << '\n';

    return 0;
}
