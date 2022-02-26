#include <iostream>
#include <vector>

bool Possible(std::vector<size_t> v, size_t m, size_t k)
{
    size_t i = 0, count = 1, s = 0;
    while (i < v.size() && s <= m && count <= k)
    {
        if (s + v[i] <= m)
        {
            s += v[i];
        }
        else
        {
            s = v[i];
            count++;
        }
        i++;
    }
    return i == v.size() && s <= m && count <= k;
}

int main()
{
    size_t k, n, sum = 0;
    std::cin >> k >> n;
    std::vector<size_t> v(n);
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> v[i];
        sum += v[i];
    }
    size_t left = 1, right = sum;
    while (right - left > 2)
    {
        size_t m = (left + right) / 2;
        if (Possible(v, m, k))
        {
            right = m;
        }
        else
        {
            left = m;
        }
    }
    size_t m = left;
    while (m <= right && !Possible(v, m, k))
    {
        m++;
    }
    std::cout << m;
    return 0;
}
