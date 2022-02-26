#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> z_function(std::string s)
{
    int n = (int)s.size();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++)
    {
       	if (i <= r)
        {
	    z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
	    z[i]++;
        }
        if (i + z[i] - 1 > r)
        {
	    l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main()
{
    std::string s;
    getline(std::cin, s);
    int k = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        std::string s1 = s.substr(0, i + 1);
        for (size_t w = 0; w < s1.size() / 2; w++)
        {
            std::swap(s1[w], s1[s1.size() - 1 - w]);
        }
        std::vector<int> Z = z_function(s1);
        int zmax = 0;
        for (unsigned j = 0; j < Z.size(); j++)
        {
            if (Z[j] > zmax)
            {
                zmax = Z[j];
            }
        }
        k += s1.size() - zmax;
    }
    std::cout << k;
    return 0;
}
