#include <stdio.h>
#include <stdbool.h>

bool isPrime(size_t N)
{
    for (size_t i = 2; i * i <= N; i++)
        if (N % i == 0)
            return false;
    return true;
}

int main()
{
    size_t N;
    scanf("%zu", &N);
    bool primes[1000];
    for (size_t i = 0; i < 1000; i++)
    {
        primes[i] = (i < 100) ? false : isPrime(i);
    }
    static size_t d[10001][10][10]; 
    for (size_t i = 0; i < 10; i++)
        for (size_t j = 0; j < 10; j++)
            for (size_t k = 0; k < 10; k++)
                d[3][k][j] += primes[100 * i + 10 * j + k];
    
    for (size_t iter = 4; iter <= N; iter++)
        for (size_t i = 0; i < 10; i++)
            for (size_t j = 0; j < 10; j++)
                for (size_t k = 0; k < 10; k++)
                    if (primes[100 * i + 10 * j + k])
                        d[iter][k][j] = (d[iter][k][j] + d[iter - 1][j][i]) % 1000000009;

    size_t count = 0;
    for (size_t i = 0; i < 10; i++)
        for (size_t j = 0; j < 10; j++)
            count = (count + d[N][i][j]) % 1000000009;
    printf("%zu", count);
    return 0;
}