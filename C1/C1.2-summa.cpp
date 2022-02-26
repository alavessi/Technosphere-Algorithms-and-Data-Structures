#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }
    for (size_t j = 0; j < n; j++)
    {
        std::cin >> b[j];
    }
    size_t i = 0, indmax1 = 0, indmax2 = 0, globmax = 0;
    int maxsum = a[0] + b[0];
    for (size_t j = 1; j < n; j++)
    {
        if (a[j] > a[globmax])
        {
            globmax = j;
        }
        if (j >= globmax)
        {
            indmax1 = globmax;
        }
        if (a[j] > a[indmax1])
        {
            i = indmax1;
            indmax1 = j;
        }
        if (a[indmax1] + b[j] > maxsum)
        {
            i = indmax1;
            indmax2 = j;
            maxsum = a[indmax1] + b[j];
        }
        else
        {
            indmax1 = i;
        }
    }
    std::cout << indmax1 << " " << indmax2;
    return 0;
}
