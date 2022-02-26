#include <stdio.h>
#include <stdbool.h>

int main()
{
    size_t N;
    scanf("%zu\n", &N);
    if (N == 3)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        printf("%lli", (long long)a * b * c);
        return 0;
    }
    long long neg1 = 1, neg2 = 1, pos1 = -1, pos2 = -1, pos3 = -1, min1 = -1000001, min2 = -1000001, min3 = -1000001;
    bool has_positive = false;
    bool has_zero = false;
    for (size_t i = 0; i < N; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        if (tmp > 0)
        {
            has_positive = true;
            if (tmp > pos1)
            {
                pos3 = pos2;
                pos2 = pos1;
                pos1 = tmp;
            }
            else if (tmp > pos2)
            {
                pos3 = pos2;
                pos2 = tmp;
            }
            else if (tmp > pos3)
            {
                pos3 = tmp;
            }
        }
        else if (tmp < 0)
        {
            if (tmp < neg1)
            {
                neg2 = neg1;
                neg1 = tmp;
            }
            else if (tmp < neg2)
            {
                neg2 = tmp;
            }

            if (tmp > min1)
            {
                min3 = min2;
                min2 = min1;
                min1 = tmp;
            }
            else if (tmp > min2)
            {
                min3 = min2;
                min2 = tmp;
            }
            else if (tmp > min3)
            {
                min3 = tmp;
            }
        }
        else
        {
            has_zero = true;
        }
    }
    long long max_product = 0;
    if (neg1 * neg2 > pos2 * pos3)
    {
        max_product = pos1 * neg1 * neg2;
    }
    else
    {
        max_product = pos1 * pos2 * pos3;
    }
    if (!has_positive)
    {
        if (has_zero)
        {
            max_product = 0;
        }
        else
        {
            max_product = min1 * min2 * min3;
        }
    }
    printf("%lli", max_product);
    return 0;
}
