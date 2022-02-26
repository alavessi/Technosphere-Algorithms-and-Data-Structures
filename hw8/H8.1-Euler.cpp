#include <cstdio>
#include <vector>
#include <set>

class Graph
{
public:
    Graph(size_t vertices);
    void add_edge(size_t from, size_t to);
    void DFS(size_t u, std::vector<bool>& visited);
    bool check_for_Eulerian_cycle();

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
    adj[to].insert(from);
}

void Graph::DFS(size_t u, std::vector<bool>& visited)
{
    visited[u] = true;
    for (auto v: adj[u])
    {
        if (!visited[v])
        {
            DFS(v, visited);
        }
    }
}

bool Graph::check_for_Eulerian_cycle()
{
    for (const auto& a: adj)
    {
        if (a.size() & 1)
        {
            return false;
        }
    }
    std::vector<bool> visited(N, false);
    DFS(0, visited);
    for (size_t i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    size_t N, M; // количества вершин и ребер графа
    scanf("%zu %zu", &N, &M);
    Graph graph(N);
    for (size_t i = 0; i < M; i++)
    {
        size_t from, to;
        scanf("%zu %zu", &from, &to);
        graph.add_edge(from - 1, to - 1);
    }
    printf("%s", graph.check_for_Eulerian_cycle() ? "YES" : "NO");
    return 0;
}
