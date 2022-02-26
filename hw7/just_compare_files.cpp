#include <iostream>
#include <fstream>

bool equal()
{
    std::ifstream f1("out1.txt"), f2("out2.txt");
    while (f1 || f2)
    {
        int x, y;
        f1 >> x;
        f2 >> y;
        std::cout << x << " " << y << std::endl;
        if (x != y) return false;
    }
    return true;
}

int main()
{
    if (equal())
    {
        std::cout << "Equal";
    }
    else
    {
        std::cout << "Not equal";
    }
    return 0;
}
