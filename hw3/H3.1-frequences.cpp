#include <iostream>
#include <string>
#include <algorithm>

struct Litera
{
    std::string c;
    size_t count;
};

int main()
{
    struct Litera L[26];
    for (int i = 0; i < 26; i++)
    {
        L[i].c = 'A' + i;
        L[i].count = 0;
    }
    std::string s;
    std::cin >> s;
    for (size_t i = 0; i < s.size(); i++)
    {
        L[s[i] - 'A'].count++;
    }
    std::sort(L, L + 26, [] (struct Litera a, struct Litera b) -> bool { return a.count > b.count || (a.count == b.count && a.c < b.c); });
    for (size_t i = 0; i < 26; i++)
    {
        if (L[i].count)
        {
            std::cout << L[i].c << " " << L[i].count << std::endl;
        }
    }
    return 0;
}
