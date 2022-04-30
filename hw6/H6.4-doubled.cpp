#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

std::pair<size_t, size_t> find_repeat(size_t N, const std::vector<size_t>& ptab, const std::vector<size_t>& htab)
{
    size_t left = 0, right = N;
    while (left + 1 < right)
    {
        size_t length = (left + right) / 2;
        std::unordered_set<size_t> s;
        bool found = false;
        for (size_t begin = 0; begin + length <= N; begin++)
        {
            size_t hash = (htab[begin + length] - htab[begin]) * ptab[N - begin];
            found = s.find(hash) != s.end();
            if (found) break;
            s.insert(hash);
        }
        if (found)
        {
            left = length;
        }
        else
        {
            right = length;
        }
    }
    for (size_t length = right; length >= left; length--)
    {
        std::unordered_set<size_t> s;
        for (size_t begin = 0; begin + length <= N; begin++)
        {
            size_t hash = (htab[begin + length] - htab[begin]) * ptab[N - begin];
            if (s.find(hash) != s.end())
            {
                return {begin, length};
            }
            s.insert(hash);
        }
    }
    return {0, 0};
}

int main()
{
    std::string str;
    std::cin >> str;
    const size_t N = str.size(), P = 29;
    std::vector<size_t> ptab(N + 1), htab(N + 1);
    ptab[0] = 1;
    htab[0] = str[0] - 'a' + 1;
    for (size_t i = 1; i <= N; i++)
    {
        ptab[i] = ptab[i - 1] * P;
        htab[i] = htab[i - 1] + (str[i - 1] - 'a' + 1) * ptab[i];
    }
    std::pair<size_t, size_t> pair = find_repeat(N, ptab, htab);
    std::cout << str.substr(pair.first, pair.second);
    return 0;
}
