#include <stdio.h>

void count_comments(size_t* v)
{ 
    enum {DEFAULT, COM1, COM2, COM3, LIT, IN1, OUT1, IN3} state = DEFAULT;
    int c;
    while ((c = getchar()) != EOF)
    {
        if ((state == IN1 && c != '*') || (state == IN3 && c != '/'))
        {
            state = DEFAULT;
        }
        if (state == OUT1 && c != ')')
        {
            state = COM1;
        }
        if (state == DEFAULT && c == '(')
        {
            state = IN1;
        }
        else if (state == IN1 && c == '*')
        {
            state = COM1;
        }
        else if (state == COM1 && c == '*')
        {
            state = OUT1;
        }
        else if (state == OUT1 && c == ')')
        {
            state = DEFAULT;
            v[1]++;
        }
        else if (state == DEFAULT && c == '{')
        {
            state = COM2;
        }
        else if (state == COM2 && c == '}')
        {
            state = DEFAULT;
            v[2]++;
        }
        else if (state == DEFAULT && c == '/')
        {
            state = IN3;
        }
        else if (state == IN3 && c == '/')
        {
            state = COM3;
        }
        else if (state == COM3 && c == '\n')
        {
            state = DEFAULT;
            v[3]++;
        }
        else if (state == DEFAULT && (int)c == 39)
        {
            state = LIT;
        }
        else if (state == LIT && c == '\n')
        {
            state = DEFAULT;
        }
        else if (state == LIT && (int)c==39)
        {
            state = DEFAULT;
            v[0]++;
        }
    }
}

int main()
{
    size_t v[4] = {0, 0, 0, 0};
    count_comments(v);
    printf("%zu %zu %zu %zu", v[1], v[2], v[3], v[0]);
    return 0;
}
