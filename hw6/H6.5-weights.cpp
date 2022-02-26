#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main()
{
    const size_t P = 29;
    std::string s;
    std::cin >> s;
    if (s.empty())
    {
        return 0;
    }
    std::vector<size_t> ptab(s.size()), htab(s.size());
    ptab[0] = 1;
    htab[0] = s[0] - 'a' + 1;
    for (size_t i = 1; i < s.size(); i++)
    {
        ptab[i] = ptab[i - 1] * P;
        htab[i] = htab[i - 1] + (s[i] - 'a' + 1) * ptab[i];
    }
    size_t max_weight = 0;
    for (size_t length = 1; length <= s.size(); length++)
    {
        std::unordered_map<size_t, size_t> counts;
        for (size_t i = s.size() - length; i > 0; i--)
        {
            size_t hash = (htab[i + length - 1] - htab[i - 1]) * ptab[s.size() - i - 1];
            counts[hash]++;
        }
        counts[htab[length - 1] * ptab[s.size() - 1]]++;
        for (auto item: counts)
        {
            max_weight = std::max(max_weight, length * item.second);
        }
    }
	std::cout << max_weight;
    return 0;
}