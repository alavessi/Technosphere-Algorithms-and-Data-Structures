#include <iostream>
#include <algorithm>

int main()
{
    size_t N;
    std::cin >> N;
    int* X = new int[N];
    int* cache = new int[N];
    for (size_t i = 0; i < N; i++)
    {
        std::cin >> X[i];
    }
    std::sort(X, X + N);
    cache[1] = X[1] - X[0];
    if (N == 2)
    {
        std::cout << cache[1];
        return 0;
    }
    cache[2] = X[2] - X[0];
    for (size_t i = 3; i < N; i++)
    {
        cache[i] = std::min(cache[i - 1], cache[i - 2]) + X[i] - X[i - 1];
    }
    std::cout << cache[N - 1];
    delete [] cache;
    delete [] X;
}
