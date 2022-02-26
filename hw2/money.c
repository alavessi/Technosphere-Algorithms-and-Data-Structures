#include <stdio.h>

int main()
{
    unsigned int N;
    scanf("%u", &N);
    unsigned long long sum = 0, S = 0;
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int a;
        scanf("%u", &a); 
        if (a > sum + 1)
        {
            S = sum + 1;
        }
        else
        {
            sum += a;
        }
    }
    if (S == 0)
    {
        S = sum + 1;
    }
    printf("%llu", S);
    return 0;
}
