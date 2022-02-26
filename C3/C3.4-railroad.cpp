#include <iostream>
#include <vector>

int main()
{
    size_t N, zero_row_count = 0, zero_col_count = 0;
    std::cin >> N;
    std::vector<std::vector<bool>> A(N, std::vector<bool>(N));
    for (size_t i = 0; i < N; i++)
    {
        bool zero_row = true;
        for (size_t j = 0; j < N; j++)
        {
            bool f;
            std::cin >> f;
            A[i][j] = f;
            zero_row &= !f;
        }
        zero_row_count += zero_row;
    }
    for (size_t i = 0; i < N; i++)
    {
        bool zero_col = true;
        for (size_t j = 0; j < N; j++)
        {
            zero_col &= !A[j][i];
        }
        zero_col_count += zero_col;
    }
    std::cout << std::max(zero_row_count, zero_col_count);
    return 0;
}