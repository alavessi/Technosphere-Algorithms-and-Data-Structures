#include <fstream>

int main()
{
    std::ofstream fout("input.txt");
    fout << 10000000 << " " << 10000 << "\n";
    for (size_t i = 0; i < 10000000; i++)
    {
        fout << i << "\n";
    }
    fout.close();
    return 0;
}
