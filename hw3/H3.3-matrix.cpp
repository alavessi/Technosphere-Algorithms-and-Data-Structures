#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t n, m, minimum = 1 << 31;
    std::cin >> n >> m;
    std::vector<std::vector<size_t> > A(n);
    for (size_t i = 0; i < n; i++)
    {
        A[i].resize(m);
    }
    for (size_t i = 0; i<n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            std::cin >> A[i][j];
        }
    }
    size_t indmin = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (A[i][j] < minimum)
            {
                minimum = A[i][j];
                indmin = j;
            }
        }
    }
    std::sort(A.begin(), A.end(), [indmin] (std::vector<size_t> a, std::vector<size_t> b) -> bool { return a[indmin] < b[indmin]; });
    std::vector<std::vector<size_t> > B(m);
    for (size_t j = 0; j < m; j++)
    {
        B[j].resize(n);
    }
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            B[j][i] = A[i][j];
        }
    }
    std::sort(B.begin(), B.end(), [] (std::vector<size_t> a, std::vector<size_t> b) -> bool { return a[0] < b[0]; });
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            std::cout << B[j][i] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
