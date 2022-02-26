#include <iostream>
#include <vector>

typedef std::vector<long long> vll;

std::vector<vll> mult(std::vector<vll> A, std::vector<vll> B, long long m)
{
    std::vector<vll> P = {{0, 0}, {0, 0}};
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                P[i][j] += (A[i][k] * B[k][j]) % m;
            }
            P[i][j] %= m;
        }
    }
    return P;
}

std::vector<vll> pow(std::vector<vll> A, long long n, long long m)
{
    if (!n)
    {
        return {{1, 0}, {0, 1}};
    }
    if (n & 1)
    {
        return mult(pow(A, n - 1, m), A, m);
    }
    std::vector<vll> B = pow(A, n >> 1, m);
    return mult(B, B, m);
}

int main()
{
    long long n, m;
    std::cin >> n >> m;
    std::vector<vll> F = {{0, 1}, {1, 1}};
    std::vector<vll> F_n = pow(F, n, m);
    std::cout << F_n[0][1] % m;
    return 0;
}
