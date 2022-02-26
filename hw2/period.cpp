#include <iostream>
#include <vector>

int main()
{
    unsigned m, n, R = 0;
    std::cin >> m >> n;
    bool per = true;
    std::vector<bool> f(n, false);
    std::vector<unsigned> q;
    q.push_back(0);
    std::cout << "0.";
    unsigned k = 0, r = m % n;
    f[r] = true;
    r *= 10;
    while (r)
    {
        k++;
        q.push_back(r / n);
        r %= n;
        if (!r)
        {
            per = false;
        }
        if (f[r])
        {
            R = r;
            break;
        }
        f[r] = true;
        r *= 10;
    }
    if (per)
    {
        unsigned i = 1;
        for (unsigned r = m; r != R; r = (10 * r) % n)
        {
            std::cout << q[i++];
        }
        std::cout << "(";
        for (unsigned j = i; j <= k; j++)
        {
            std::cout << q[j];
        }
        std::cout << ")";
    }
    else
    {
        for (unsigned i = 1; i <= k; i++)
        {
            std::cout << q[i];
        }
    }
    return 0;
}
