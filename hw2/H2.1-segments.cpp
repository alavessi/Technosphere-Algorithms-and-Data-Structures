#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N;
    std::cin >> N;
    if (N == 0)
    {
        std::cout << 0;
        return 0;
    }
    std::vector<double> x(N);
    for (size_t i = 0; i < N; i++)
    {
        std::cin >> x[i];
    }
    std::sort(x.begin(), x.end());
    double pos = x[0];
    size_t k = 1;
    for (size_t i = 1; i < N; i++)
    {
        if (x[i] - pos > 1.0)
        {
            pos = x[i];
            k++;
        }
    }
    std::cout << k;
    return 0;
}