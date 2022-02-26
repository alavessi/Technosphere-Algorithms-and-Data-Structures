#include <stdio.h>

size_t f(size_t n, size_t i)
{
    if (n < 10)
    {
		    if (i == 0)
        {
            return n;
        }
        size_t y = 1 << (n - 1);
        return (i < y) ? f(n - 1, i - 1) : f(n - 1, y + y - 2 - i);
	  }
	  else if (n == 10)
    {
        if (i < 2)
        {
            return 1 - i;
        }
        size_t y = 1 << (n - 1);
        return f(n - 1, i - (i <= y ? 2 : 2 * (i - y) + 1));
    }
    else
    {
        if (i == 0)
        {
            return n / 10;
        }
        if (i == 1)
        {
            return n % 10;
        }
        size_t b = (1 << (n - 1)) + (1 << (n - 10)) - 1;
        return f(n - 1, i - (i <= b ? 2 : 2 * (i - b) + 1));
    }
}

int main()
{
    size_t n, m, p;
    scanf("%zu %zu", &n, &m);
    for (size_t i = 1; i <= m; i++)
    {
        scanf("%zu", &p);
        printf("%zu\n", f(n, p - 1));
    }
    return 0;
}
