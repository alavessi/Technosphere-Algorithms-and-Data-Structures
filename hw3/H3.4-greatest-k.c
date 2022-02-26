#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 1000000

typedef struct BinaryHeap
{
    long long* body;
    size_t size;
} BinaryHeap;

void sift_down(BinaryHeap* bh, size_t i)
{
    while ((i << 1) + 1 < bh->size)
    {
        size_t left = (i << 1) + 1;
        size_t right = (i << 1) + 2;
        size_t j = left;
        if (right < bh->size && bh->body[right] > bh->body[left])
        {
            j = right;
        }
        if (bh->body[i] >= bh->body[j])
        {
            break;
        }
        long long t = bh->body[i];
        bh->body[i] = bh->body[j];
        bh->body[j] = t;
        i = j;
    }
}

void build(BinaryHeap* bh)
{
    for (int i = bh->size >> 1; i >= 0; i--)
    {
        sift_down(bh, i);
    }
}

long long extract_max(BinaryHeap* bh)
{
    long long max = bh->body[0];
    bh->body[0] = bh->body[--(bh->size)];
    sift_down(bh, 0);
    return max;
}

long long read_unlocked()
{
    long long x = 0;
    bool neg = false;
    int c = getchar_unlocked();
    while (c != '-' && !('0' <= c && c <= '9'))
    {
        c = getchar_unlocked();
    }
    if (c == '-')
    {
        neg = true;
        c = getchar_unlocked();
    }
    while ('0' <= c && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar_unlocked();
    }
    return neg ? -x : x;
}

int main()
{
    size_t N, K, size = 0, done = 0;
    scanf("%zu %zu", &N, &K);
    long long* max = (long long*) malloc(100000 * sizeof(long long));
    while (done < N)
    {
        size_t M = (N - done < MAXSIZE) ? N - done : MAXSIZE;
        long long* a = (long long*) malloc(M * sizeof(long long));
        for (size_t i = 0; i < M; i++)
        {
            a[i] = read_unlocked();
        }
        BinaryHeap bh = {a, M};
        build(&bh);
        for (size_t i = 0; i < (K < M ? K : M); i++)
        {
            max[size++] = extract_max(&bh);
        }
        done += MAXSIZE;
        free(a);
    }
    BinaryHeap bh = {max, size};
    build(&bh);
    for (size_t i = 0; i < K; i++)
    {
        printf("%lld\n", extract_max(&bh));
    }
    free(max);
    return 0;
}