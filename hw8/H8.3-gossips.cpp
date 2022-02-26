#include <iostream>
#include <vector>
#include <set>

const int INF = 1E9;

class Graph
{
public:
    Graph(size_t vertices);
    void add_edge(size_t from, size_t to);
    std::vector<std::vector<int>> Floyd_Warshall();

private:
    size_t N;
    std::vector<std::vector<bool>> adj; // хранение графа в виде матрицы смежности
};

Graph::Graph(size_t vertices)
{
    N = vertices;
    adj.resize(N, std::vector<bool>(N, false));
}

void Graph::add_edge(size_t from, size_t to)
{
    adj[from][to] = adj[to][from] = true;
}

std::vector<std::vector<int>> Graph::Floyd_Warshall()
{
    std::vector<std::vector<int>> d(N, std::vector<int>(N));
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            d[i][j] = (adj[i][j]) ? adj[i][j] : INF; 
        }
    }
    for (size_t i = 0; i < N; i++)
    {
	    for (size_t j = 0; j < N; j++)
        {
		    for (size_t k = 0; k < N; k++)
			{
                if (d[j][i] < INF && d[i][k] < INF)
				{
                    d[j][k] = std::min(d[j][k], d[j][i] + d[i][k]);
                }
            }
        }
    }
    for (size_t i = 0; i < N; i++)
    {
        d[i][i] = 0;
    }
    return d;
}

int main()
{
    size_t N, M, K;
    std::cin >> N >> M >> K;
    Graph graph(N * M);
    for (size_t i = 0; i < M; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            size_t current = i * N + j;
            if (i)
            {
                graph.add_edge(current, current - N);
            }
            if (j)
            {
                graph.add_edge(current, current - 1);
            }
            if (i < M - 1)
            {
                graph.add_edge(current, current + N);
            }
            if (j < N - 1)
            {
                graph.add_edge(current, current + 1);
            }
        }
    }
    auto distances = graph.Floyd_Warshall();
    std::vector<int> mindistances(N * M, INF);
    for (size_t i = 0; i < K; i++)
    {
        size_t x, y;
        std::cin >> x >> y;
        size_t source = x * N + y;
        for (size_t j = 0; j < N * M; j++)
        {
            mindistances[j] = std::min(mindistances[j], distances[source][j]);
        }
    }
    int rounds_count = 0;
    for (auto d: mindistances)
    {
        rounds_count = std::max(rounds_count, d);
    }
    std::cout << rounds_count;
    return 0;
}