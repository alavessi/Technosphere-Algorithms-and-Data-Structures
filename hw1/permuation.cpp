#include <cstdio>
#include <vector>

size_t Fact(size_t n)
{
    size_t F = 1;
    for (size_t i = 2; i <= n; i++)
    {
        F *= i;
    }
    return F;
}

size_t NotUsed(std::vector<bool>& used, size_t blockNum)
{
    size_t j, pos = 0;
    for (j = 1; j < used.size(); j++)
    {
        if (!used[j])
        {
            pos++;
        }
        if (blockNum == pos)
        {
            break;
        }
    }
    return j;
}

int main()
{
    size_t n, m;
    scanf("%zu %zu", &n, &m);
    std::vector<size_t> res(n);
    std::vector<bool> used(n + 1, false);
    for (size_t i = 0; i < n; i++)
    {
        size_t F = Fact(n - 1 - i);
        size_t j = NotUsed(used, (m - 1) / F + 1);
        res[i] = j;
        used[j] = true;
        m = (m - 1) % F + 1;
    }
    for (size_t i = 0; i < n; i++)
    {
        printf("%zu ", res[i]);
    }
    return 0;
}
