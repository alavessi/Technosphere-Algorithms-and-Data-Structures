#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

struct Man
{
    unsigned weight, force;
};

int main()
{
    unsigned n, k = 0, sum_weight = 0;
    std::cin >> n;
    std::vector<struct Man> men(n);
    for (unsigned i = 0; i < n; i++)
    {
        std::cin >> men[i].weight >> men[i].force;
    }
    std::sort(men.begin(), men.end(), [] (Man lhs, Man rhs) -> bool { return std::tie(lhs.weight, lhs.force) < std::tie(rhs.weight, rhs.force); });
    for (unsigned i = 0; i < n; i++)
    {
        if (men[i].force >= sum_weight)
        {
            k++;
            sum_weight += men[i].weight;
        }
    }
    std::cout << k;
    return 0;
}
