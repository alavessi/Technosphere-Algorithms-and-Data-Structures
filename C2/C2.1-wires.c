#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t N, K, M = 0, sum = 0;
    scanf("%zu %zu", &N, &K);
    size_t* w = (size_t*) malloc(N * sizeof(size_t));
    for (size_t i = 0; i < N; i++)
    {
        scanf("%zu", &w[i]);
        sum += w[i];
    }
    size_t left = 0, right = sum;
    while (left + 1 < right)
    {
        size_t mid = (left + right) / 2, k = 0;
        for (size_t i = 0; i < N; i++)
        {
            k += w[i] / mid;
        }
        if (k >= K)
        {
            left = mid;
            M = (mid > M) ? mid : M;
        }
        else
        {
            right = mid;
        }
    }
    printf("%zu", M);
    free(w);
    return 0;
}