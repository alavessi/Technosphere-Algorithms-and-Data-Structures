#include <cstdio>
#include <set>

int main()
{
    size_t N;
    scanf("%zu", &N);
    int query, median;
    scanf("%d %d", &query, &median);
    std::multiset<int> less_than_median, more_than_median;
    bool disbalance = false; // disbalance = more_than_median.size() - less_than_median.size()
    for (size_t i = 1; i < N; i++)
    {
        int query;
        scanf("%d", &query);
        switch (query)
        {
            case 0:
            int value;
            scanf("%d", &value);
            if (disbalance)
            {
                if (value <= median)
                {
                    less_than_median.insert(value);
                }
                else
                {
                    more_than_median.insert(value);
                    less_than_median.insert(median);
                    auto it = more_than_median.begin();
                    median = *it;
                    more_than_median.erase(it);
                }
            }
            else
            {
                if (value <= median)
                {
                    less_than_median.insert(value);
                    more_than_median.insert(median);
                    auto it = std::prev(less_than_median.end());
                    median = *it;
                    less_than_median.erase(it);
                }
                else
                {
                    more_than_median.insert(value);
                }
            }
            disbalance ^= 1;
            break;

            case 1:
            scanf("%d", &value);
            if (less_than_median.find(value) == less_than_median.end() && value != median && more_than_median.find(value) == more_than_median.end())
                break;
            if (disbalance)
            {
                if (value <= median)
                {
                    if (value < median)
                    {
                        less_than_median.erase(less_than_median.find(value));
                        less_than_median.insert(median);
                    }
                    auto it = more_than_median.begin();
                    median = *it;
                    more_than_median.erase(it);
                }
                else
                {
                    more_than_median.erase(more_than_median.find(value));
                }
            }
            else
            {
                if (value < median)
                {
                    less_than_median.erase(less_than_median.find(value));
                }
                else
                {
                    if (value > median)
                    {
                        more_than_median.erase(more_than_median.find(value));
                        more_than_median.insert(median);
                    }
                    auto it = std::prev(less_than_median.end());
                    median = *it;
                    less_than_median.erase(it);
                }
            }
            disbalance ^= 1;
            break;

            case 2:
            printf("%d\n", median);
            break;
        }
    }
    return 0;
}