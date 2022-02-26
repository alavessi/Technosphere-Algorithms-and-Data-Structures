#include <stdio.h>
#include <stdbool.h>

bool match(const char* sometext, const char* pattern, size_t i, size_t j)
{
    while (sometext[i] != '\0' && pattern[j] != '\0')
    {
        if (sometext[i] != pattern[j] && pattern[j] != '?')
        {
            if (pattern[j] == '*')
            {
                if (pattern[j + 1] == '\0') return true;
                for (size_t k = i; sometext[k] != '\0'; k++)
                {
                    if (match(sometext, pattern, k, j + 1)) return true;
                }
                return false;
            }
            else return false;
        }
        else
        {
            i++;
            j++;
        }
    }
    return sometext[i] == '\0' && (pattern[j] == '\0' || (pattern[j] == '*' && pattern[j + 1] == '\0'));
}

int main()
{
    const size_t MAXSIZE = 700;
    char sometext[MAXSIZE + 1], pattern[MAXSIZE + 1];
    scanf("%s%s", sometext, pattern);
    if (match(sometext, pattern, 0, 0))
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
    return 0;
}