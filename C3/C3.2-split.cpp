#include <iostream>
#include <vector>

class Solver
{
public:
    Solver(size_t N)
    {
        cache.resize(N + 1, std::vector<int>(N + 1, -1));
    }

    int F(int n, int prev_level)
    {
        if (n < 0 || prev_level < 0) return 0;
	if (prev_level == 1) return n == 1;
	else if (n <= 2) return 1;
        if (cache[n][prev_level] >= 0) return cache[n][prev_level];
	return cache[n][prev_level] = (F(n, prev_level - 1) + F(n - prev_level, prev_level - 1)) % 1000000007;
    }

private:
    std::vector<std::vector<int>> cache;
};

int main()
{
    int N;
    std::cin >> N;
    Solver solver(N);
    std::cout << solver.F(N, N);
    return 0;
}
