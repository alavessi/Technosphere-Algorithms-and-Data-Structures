#include <cstdio>
#include <vector>
#include <map>
#include <unordered_map>

const size_t INF = 100000;

struct T
{
    std::vector<size_t> indexes;
    size_t current_position = 0;
};

struct Cache
{
    std::unordered_map<unsigned long long, size_t> actual;
    std::map<size_t, unsigned long long> pairs;
};

int main()
{
    size_t N, M;
    scanf("%zu %zu", &N, &M);
    std::vector<unsigned long long> queries(M);
    std::vector<size_t> next_index(M, INF);
    std::unordered_map<unsigned long long, T> appearances;
    for (size_t i = 0; i < M; i++)
    {
        scanf("%llu", &queries[i]);
        next_index[i] += i;
        appearances[queries[i]].indexes.push_back(i);
    }
    for (size_t i = 0; i < M; i++)
    {
        if (appearances[queries[i]].indexes.size() > appearances[queries[i]].current_position + 1)
        {
            next_index[i] = appearances[queries[i]].indexes[++appearances[queries[i]].current_position];
        }
    }
    
    Cache cache;
    size_t count = 0;
    for (size_t i = 0; i < M; i++)
    {
        if (cache.actual.find(queries[i]) == cache.actual.end())
        {
            if (cache.actual.size() >= N)
            {
                auto it = std::prev(cache.pairs.end());
                cache.actual.erase(it->second);
                cache.pairs.erase(it);
            }
            cache.actual[queries[i]] = next_index[i];
            cache.pairs[next_index[i]] = queries[i];
            count++;
        }
        else
        {
            cache.pairs.erase(cache.actual[queries[i]]);
            cache.actual[queries[i]] = next_index[i];
            cache.pairs[next_index[i]] = queries[i];
        }
    }
    printf("%zu", count);
    return 0;
}