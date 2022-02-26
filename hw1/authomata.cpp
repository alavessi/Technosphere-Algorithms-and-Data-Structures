#include <iostream>

int main()
{
    int N, k = 0, temp = 0;
    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        int a;
        std::cin >> a;
        if (a == 5)
        {
            temp = std::max(temp, k);
            k--;
        }
        else
        {
            k += a / 5 - 1;
        }
    }
    std::cout << std::max(temp, k);
    return 0;
}
