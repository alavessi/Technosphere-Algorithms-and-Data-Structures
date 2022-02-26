#include <stdio.h>

int isSquare(int N)
{
    int i;
    for (i = 1; i * i < N; i++);
    return i * i == N;
}

int count_of_squares(int N)
{
    if (isSquare(N))
    {
        return 1;
    }
    for (int i = 1; i * i < N; i++)
    {
        if (isSquare(N - i * i))
        {
            return 2;
        }
    }
    while (N % 4 == 0)
    {
        N /= 4;
    }
    return 3 + (N % 8 == 7);
}

int main()
{
    int N;
    scanf("%d", &N);
    printf("%d", count_of_squares(N));
    return 0;
}
