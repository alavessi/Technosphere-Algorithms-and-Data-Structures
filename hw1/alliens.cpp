#include <cstdio>
#include <string>

std::string Get_line(char c)
{
    std::string s;
    int j = 0;
    while ((c = getchar()) != '\n')
    {
        s[j] = c;
        j++;
    }
    s[j] = '\0';
    return s;
}

int main()
{
    unsigned int k = 0, N;
    scanf("%d\n", &N);
    char c;
    unsigned long long prev = atoll(Get_line(c).c_str());
    for (unsigned int i = 1; i < N; i++)
    {
        unsigned long long temp = atoll(Get_line(c).c_str());
        unsigned long long curr = temp;
        while(prev != 0 && temp != 0)
        {
            unsigned long long t = temp;
            temp = prev % temp;
            prev = t;
        }
        k += (prev + temp) != 1;
        prev = curr;
    }
    printf("%u", k);
    return 0;
}
