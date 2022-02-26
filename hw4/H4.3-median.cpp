#include <cstdio>
#include <queue>

int main()
{
    int N;
    scanf("%d", &N);
    int query, median;
    scanf("%d %d", &query, &median);
    std::priority_queue<int> less_than_median;
    std::priority_queue<int, std::vector<int>, std::greater<int>> more_than_median;
    bool balance = false; // balance = more_than_median.size() - less_than_median.size()
    for (int i = 1; i < N; i++)
    {
        int query;
        scanf("%d", &query);
        if (query)
        {
            printf("%d\n", median);
        }
        else
        {
            int value;
            scanf("%d", &value);
            if (balance)
            {
                if (value <= median)
                {
                    less_than_median.push(value);
                }
                else
                {
                    more_than_median.push(value);
                    less_than_median.push(median);
                    median = more_than_median.top();
                    more_than_median.pop();
                }
            }
            else
            {
                if (value <= median)
                {
                    less_than_median.push(value);
                    more_than_median.push(median);
                    median = less_than_median.top();
                    less_than_median.pop();
                }
                else
                {
                    more_than_median.push(value);
                }
            }
            balance ^= 1;
        }
    }
    return 0;
}