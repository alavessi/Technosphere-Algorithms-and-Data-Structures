#include <cstdio>
#include <string>

int main()
{
    unsigned n, k, m = 0;
    scanf("%u%u", &n, &k);
    std::string s = std::to_string(k);
    for (unsigned i = 0; i < n; i++)
    {
        m += std::to_string(i) <= s;
    }
    printf("%u", m);
    return 0;
}
