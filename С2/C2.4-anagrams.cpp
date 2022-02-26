#include <iostream>
#include <vector>
#include <set>

int main()
{
    size_t N;
    std::cin >> N;
    std::set<std::vector<unsigned>> s;
    for (size_t i = 0; i < N; i++)
    {
        std::vector<unsigned> a(26, 0);
        int c = getchar_unlocked();
        while ('A' > c || c > 'Z')
        {
            c = getchar_unlocked();
        }
        while('A' <= c && c <= 'Z')
        {
            a[c - 'A']++;
            c = getchar_unlocked();
        }
        s.insert(a);
    }
    std::cout << s.size();
    return 0;
}