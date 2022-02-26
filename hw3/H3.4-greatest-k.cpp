#include <cstdio>
#include <algorithm>

#define MAXSIZE 1000000

class BinaryHeap
{
private:
    long long* body;
    size_t size;

public:
    inline BinaryHeap(long long* p, size_t new_size);
    inline void sift_down(size_t i);
    inline void build();
    inline long long extract_max();
};

inline BinaryHeap::BinaryHeap(long long* p, size_t new_size)
{
    body = p;
    size = new_size;
}

inline void BinaryHeap::sift_down(size_t i)
{
    while ((i << 1) + 1 < size)
    {
        size_t left = (i << 1) + 1;
        size_t right = (i << 1) + 2;
        size_t j = left;
        if (right < size and body[right] > body[left])
        {
            j = right;
        }
        if (body[i] >= body[j])
        {
            break;
        }
        std::swap(body[i], body[j]);
        i = j;
    }
}

inline void BinaryHeap::build()
{
    for (int i = size >> 1; i >= 0; i--)
    {
        sift_down(i);
    }
}

inline long long BinaryHeap::extract_max()
{
    long long max = body[0];
    body[0] = body[--size];
    sift_down(0);
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
    int N;
    size_t K, size = 0;
    scanf("%d %zu", &N, &K);
    long long* max = new long long[100000];
    while (N > 0)
    {
        size_t M = std::min(N, MAXSIZE);
        long long* a = new long long[M];
        for (size_t i = 0; i < M; i++)
        {
            a[i] = read_unlocked();
        }
        BinaryHeap bh(a, M);
        bh.build();
        for (size_t i = 0; i < std::min(K, size_t(N)); i++)
        {
            max[size++] = bh.extract_max();
        }
        delete [] a;
        N -= MAXSIZE;
    }
    BinaryHeap bh(max, size);
    bh.build();
    for (size_t i = 0; i < K; i++)
    {
        printf("%lli\n", bh.extract_max());
    }
    delete [] max;
    return 0;
}