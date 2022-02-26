#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Record_time
{
    unsigned sin, sout;
};

bool cmp_out(struct Record_time a, struct Record_time b)
{
	return a.sout < b.sout || a.sout == b.sout && a.sin < b.sin;
}

int main()
{
    unsigned n, curmax = 1, globmax = 1;
    std::cin >> n;
    std::vector<struct Record_time> records(n);
    std::string s1, s2;
    for (unsigned i = 0; i < n; i++)
    {
        std::cin >> s1 >> s2;
        records[i].sin = 3600 * atoi(s1.substr(0, 2).c_str()) + 60 * atoi(s1.substr(3, 2).c_str()) + atoi(s1.substr(6, 2).c_str());
        records[i].sout = 3600 * atoi(s2.substr(0, 2).c_str()) + 60 * atoi(s2.substr(3, 2).c_str()) + atoi(s2.substr(6, 2).c_str());
    }
    std::sort(records.begin(),records.end(), &cmp_out);
    unsigned frontier = records[0].sout;
    for (unsigned i = 1; i < n; i++)
    {
        if (records[i].sin <= frontier)
        {
            curmax++;
        }
        else
        {
            globmax = std::max(globmax, curmax);
            unsigned j = i;
            while (j > 0 && records[j].sout >= records[i].sin)
            {
                j--;
            }
            curmax = i - j;
            frontier = records[j + 1].sout;
        }
    }
    std::cout << std::max(globmax, curmax);
    return 0;
}
