#include <stdio.h>
#include <stdbool.h>

int main()
{
    unsigned st = 0, k = 0;
    bool f = false;
    int c = getchar();
    while (c != '\n')
    {
        if (f)
        {
            if (c == '(')
            {
                st++;
            }
            else if (c == ')')
            {
                if (st)
                {
                    st--;
                }
                else
                {
                    f = false;
                }
            }
            else if (c == 'w')
            {
                k++;
            }
        }
        else if (c == 'b')
        {
            f = true;
        }
        c = getchar();
    }
    printf("%u", k);
    return 0;
}
