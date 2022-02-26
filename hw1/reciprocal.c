#include <stdio.h>

size_t BinPow(size_t a, size_t n, size_t m)
{
    if (n == 0)
    {
        return 1;
    }
    if (n % 2 != 0)
    {
        return (a * BinPow(a, n - 1, m)) % m;
    }
    size_t b = BinPow(a, n >> 1, m);
    return (b * b) % m;
}

int main()
{
    size_t p, m;
    scanf("%zu %zu", &p, &m);
    size_t q = BinPow(p, m - 2, m);
    printf("%zu", q);
    return 0;
}
