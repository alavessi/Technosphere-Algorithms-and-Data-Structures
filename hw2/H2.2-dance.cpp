#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t L, N;
    std::cin >> L >> N;
    std::vector<int> v(N);
    for (size_t i = 0; i < N; i++)
    {
        std::cin >> v[i];
    }
    std::sort(v.begin(), v.end());
    size_t count = 1;
    int pos = v[0];
    for (size_t i = 1; i < N; i++)
    {
        if (abs(v[i] - pos) > 2 * L)
        {
            count++;
            pos = v[i];
        }
    }
    std::cout << count;
    return 0;
}