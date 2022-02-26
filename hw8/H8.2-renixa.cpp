#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

class Graph
{
public:
    Graph(size_t vertices);
    void add_edge(size_t from, size_t to);
    void DFS(size_t u, std::vector<bool>& visited, std::vector<size_t>& ans);
    std::vector<size_t> topological_sort();

private:
    size_t N;
    std::vector<std::set<size_t>> adj; // хранение графа в виде множеств смежности
};

Graph::Graph(size_t vertices)
{
    N = vertices;
    adj.resize(N);
}

void Graph::add_edge(size_t from, size_t to)
{
    adj[from].insert(to);
}

void Graph::DFS(size_t u, std::vector<bool>& visited, std::vector<size_t>& ans)
{
    visited[u] = true;
    for (auto v: adj[u])
    {
        if (!visited[v])
        {
            DFS(v, visited, ans);
        }
    }
    ans.push_back(u);
}

std::vector<size_t> Graph::topological_sort()
{
    std::vector<size_t> ans;
    std::vector<bool> visited(N, false);
    for (size_t i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            DFS(i, visited, ans);
        }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

int main()
{
    size_t N, M; // количества вершин и ребер графа
    std::cin >> N >> M; 
    Graph graph(N);
    std::vector<std::string> words(M);
    for (size_t i = 0; i < M; i++)
    {
        std::cin >> words[i];
    }
    for (size_t i = 0; i < M - 1; i++)
    {
        for (size_t j = i + 1; j < M; j++)
        {
            std::string s1 = words[i], s2 = words[j];
            size_t ind, len = std::min(s1.size(), s2.size());
            for (ind = 0; ind < len && s1[ind] == s2[ind]; ind++);
            if (ind < len)
            {
                graph.add_edge(s1[ind] - 'A', s2[ind] - 'A');
            }
        }
    }
    std::vector<size_t> cipher = graph.topological_sort();
    for (auto c: cipher)
    {
        std::cout << char(c + 'A');
    }
    return 0;
}