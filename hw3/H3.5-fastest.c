#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int N, K, M, L;
    scanf("%u %u %u %u", &N, &K, &M, &L);
    unsigned int* A = (unsigned int*) malloc(N * sizeof(unsigned int));
    unsigned int* B = (unsigned int*) malloc(N * sizeof(unsigned int));
    unsigned int C[256];
    A[0] = K;
    for (unsigned int i = 0; i < N - 1; i++)
    {
        A[i + 1] = (unsigned int)((A[i] * (unsigned long long)M) & 0xFFFFFFFFU) % L;
    }
    for (unsigned int i = 0; i < 256; i++)
    {
        C[i] = 0;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int d = A[i] & 0xFF;
        C[d]++;
    }
    unsigned int count = 0;
    for (unsigned int i = 0; i < 256; i++)
    {
        unsigned int tmp = C[i];
        C[i] = count;
        count += tmp;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int d = A[i] & 0xFF;
        B[C[d]] = A[i];
        C[d]++;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        A[i] = B[i];
    }

    for (unsigned int i = 0; i < 256; i++)
    {
        C[i] = 0;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int d = (A[i] >> 8) & 0xFF;
        C[d]++;
    }
    count = 0;
    for (unsigned int i = 0; i < 256; i++)
    {
        unsigned int tmp = C[i];
        C[i] = count;
        count += tmp;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int d = (A[i] >> 8) & 0xFF;
        B[C[d]] = A[i];
        C[d]++;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        A[i] = B[i];
    }

    for (unsigned int i = 0; i < 256; i++)
    {
        C[i] = 0;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int d = (A[i] >> 16) & 0xFF;
        C[d]++;
    }
    count = 0;
    for (unsigned int i = 0; i < 256; i++)
    {
        unsigned int tmp = C[i];
        C[i] = count;
        count += tmp;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int d = (A[i] >> 16) & 0xFF;
        B[C[d]] = A[i];
        C[d]++;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        A[i] = B[i];
    }

    for (unsigned int i = 0; i < 256; i++)
    {
        C[i] = 0;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int d = (A[i] >> 24) & 0xFF;
        C[d]++;
    }
    count = 0;
    for (unsigned int i = 0; i < 256; i++)
    {
        unsigned int tmp = C[i];
        C[i] = count;
        count += tmp;
    }
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int d = (A[i] >> 24) & 0xFF;
        B[C[d]] = A[i];
        C[d]++;
    }

    unsigned long long sum = 0;
    for (unsigned int i = 0; i < N; i += 2)
    {
        sum += (unsigned long long)B[i] % L;
        sum %= L;
    }
    printf("%llu", sum % L);
    free(A);
    free(B);
    return 0;
}