#include <iostream>
#include <vector>

const int INF = 1E9;

class Graph
{
public:
    Graph(size_t vertices);
    friend std::istream& operator>>(std::istream& is, Graph& graph);
    std::vector<std::vector<int>> Floyd_Warshall();
    
private:
    size_t N;
    std::vector<std::vector<int>> adj; // хранение взвешенного орграфа в виде матрицы смежности
};

Graph::Graph(size_t vertices)
{
    N = vertices;
    adj.resize(N, std::vector<int>(N));
}


std::istream& operator>>(std::istream& is, Graph& graph)
{
    for (size_t i = 0; i < graph.N; i++)
    {
        for (size_t j = 0; j < graph.N; j++)
        {
            is >> graph.adj[i][j];
        }
    }
    return is;
}

std::vector<std::vector<int>> Graph::Floyd_Warshall()
{
    std::vector<std::vector<int>> d(N, std::vector<int>(N));
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            d[i][j] = (adj[i][j] >= 0) ? adj[i][j] : INF; 
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
    return d;
}

int main()
{
    size_t N; // количество вершин графа
    std::cin >> N;
    Graph graph(N);
    std::cin >> graph;
    auto d = graph.Floyd_Warshall();
    int diameter = 0;
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (d[i][j] < INF && d[i][j] > diameter)
            {
                diameter = d[i][j];
            }
        }
    }
    std::cout << diameter;
    return 0;
}
