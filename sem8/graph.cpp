#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <queue>
#include <ctime>
#include <cassert>

using namespace std;

struct graph { // невзвешенный неориентированный граф
    // Вариант: хранение в виде матрицы связей
    graph(size_t vertices) {
        N = vertices;
        adj.resize(N);
    }
    vector<vector<size_t>> adj;
    size_t N;

    enum color {WHITE, GRAY, BLACK};
    void add_edge(size_t from, size_t to) {
        assert(from < N);
        assert(to < N);
        adj[from].push_back(to);
        adj[to].push_back(from);
    }

    void print(const char *prefix) const {
        printf("%s:\n", prefix);
        for (auto const &a: adj) {
            for (auto q: a) {
                printf("%zu ", q);
            }
            printf("\n");
        }
    }

    vector<int> bfs(size_t root) {
        vector<int> d(N,-1);
        vector<color> c(N, WHITE);
        assert(root < N);
        d[root] = 0;
        c[root] = GRAY;
        queue<size_t> q;
        q.push(root);

        while (!q.empty()) {
            auto u = q.front(); q.pop();
            assert (c[u] == GRAY);
            for (auto v: adj[u]) {
                if (c[v] == WHITE) {
                    d[v] = d[u] + 1;
                    c[v] = GRAY;
                    q.push(v);
                }
            }
            c[u] = BLACK;
        }
        return d;
    }

    void dfs_recursive(size_t u, vector<pair<size_t, size_t>> &ret, 
            vector<color> &color, size_t &time) {
        color[u] = GRAY;
        ret[u].first = ++time;
        for (auto v: adj[u]) {
            if (color[v] == WHITE) {
                dfs_recursive(v, ret, color, time);
            }
        }
        ret[u].second = ++time;
        color[u] = BLACK;
    }

    auto dfs() {
        vector<pair<size_t, size_t>> ret(N);
        vector<color> color(N,WHITE);
        size_t time = 0;
        for (size_t i = 0; i < N; i++) {
            if (color[i] == WHITE) {
                dfs_recursive(i, ret, color, time);
            }
        }
        return ret;
    }
};

int main() {
    int n; // Вершин
    int m; // Рёбер
    scanf("%d%d", &n, &m);
    graph g(n);
    for (int i = 0; i < m; i++) {
        int from, to;
        scanf("%d%d", &from, &to);
        g.add_edge(from, to);
    }
    // g.print("Initial graph");
    clock_t start = clock();
    //auto d = g.bfs(0);
    auto d = g.dfs();
    clock_t end = clock();
    for (auto q: d) {
        printf("%zu/%zu ", q.first, q.second);
    }
    printf("\n");
    fprintf(stderr, "time = %.5lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}
