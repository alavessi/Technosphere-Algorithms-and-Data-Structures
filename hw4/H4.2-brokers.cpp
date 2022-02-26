#include <cstdio>
#include <queue>

typedef unsigned long long ull;

int main()
{
    size_t N;
    scanf("%zu", &N);
    std::priority_queue<ull, std::vector<ull>, std::greater<ull>> q;
    for (size_t i = 0; i < N; i++)
    {
        ull x;
        scanf("%llu", &x);
        q.push(x);
    }
    ull sum = 0;
    while (q.size() > 1)
    {
        ull a = q.top();
        q.pop();
        ull b = q.top();
        q.pop();
        q.push(a + b);
        sum += a + b;
    }
    printf("%llu.%02llu", sum / 100, sum % 100);
    return 0;
}
