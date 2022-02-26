#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    unsigned int V, n;
    unsigned long long sum = 0;
    std::cin >> V >> n;
    std::vector<unsigned int> c(n);
    for (unsigned int i = 0; i < n; i++)
    {
        std::cin >> c[i];
        sum += c[i];
    }
    if (2 * sum < V)
    {
        std::cout << "Impossible";
        return 0;
    }
    if (2 * sum == V)
    {
        std::cout << 2 * n;
        return 0;
    }
    unsigned int K = 2 * n + 1;
    const unsigned int lim = pow(3, n);
    for (unsigned int i = 1; i < lim - 1; i++)
    {
        unsigned int k = i;
        unsigned int length = floor(log(i) / log(3)) + 1;
        sum = 0;
        unsigned int cur = 0;
        for (int j = n - 1; j >= int(n - length); j--)
        {
            cur += k % 3;
            sum += k % 3 * c[j];
            if (cur >= K || sum >= V)
            {
                break;
            }
            k /= 3;
        }
        if (sum == V)
        {
            K = std::min(cur, K);
        }
    }
    if (K > 2 * n)
    {
        std::cout << "Change";
    }
    else
    {
        std::cout << K;
    }
    return 0;
}
