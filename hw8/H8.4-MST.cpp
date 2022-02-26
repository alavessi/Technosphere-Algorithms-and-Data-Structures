#include <iostream>
#include <vector>
#include <map>
#include <set>

class Graph
{
public:
    Graph(size_t vertices);
    void add_edge(size_t from, size_t to, size_t weight);
    std::set<std::pair<int, int>> MST_Prim();
    std::map<std::pair<size_t, size_t>, size_t> weights; //хранение взвешенного графа в виде списка ребер

private:
    size_t N;
    std::vector<std::set<std::pair<size_t, size_t>>> adj; // хранение взвешенного графа в виде множеств смежности
};

Graph::Graph(size_t vertices)
{
    N = vertices;
    adj.resize(N);
}

void Graph::add_edge(size_t from, size_t to, size_t weight)
{
    adj[from].insert({to, weight});
    adj[to].insert({from, weight});
    weights[{from, to}] = weights[{to, from}] = weight;
}
 
std::set<std::pair<int, int>> Graph::MST_Prim()
{
    const int INF = 1000000000;
    std::vector<size_t> min_e(N, INF);
    std::vector<int> sel_e(N, -1);
    std::set<std::pair<int, int>> ans;
    min_e[0] = 0;
    std::set<std::pair<int,int>> q;
    q.insert({0, 0});
    for (size_t i = 0; i < N; i++)
    {
	    int v = q.begin()->second;
	    q.erase(q.begin());
	    if (sel_e[v] != -1 && ans.find({sel_e[v], v}) == ans.end())
        {
            ans.insert({v, sel_e[v]});
        }
	    for (const auto& [to, weight]: adj[v])
        {
		    if (weight < min_e[to])
            {
			    q.erase({min_e[to], to});
			    min_e[to] = weight;
			    sel_e[to] = v;
			    q.insert({min_e[to], to});
		    }
	    }
    }
    return ans;
}

int main()
{
    size_t N, M; // количества вершин и ребер графа
    std::cin >> N >> M;
    Graph graph(N);
    for (size_t i = 0; i < M; i++)
    {
        size_t from, to, weight;
        std::cin >> from >> to >> weight;
        graph.add_edge(from - 1, to - 1, weight);
        
    }
    auto MST = graph.MST_Prim();
    size_t MST_SummaryCost = 0;
    for (const auto& edge: MST)
    {
        MST_SummaryCost += graph.weights[edge];
    }
    std::cout << MST_SummaryCost;
    return 0;
}