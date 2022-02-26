#include <iostream>
#include <map>

class Solver
{
public:
    int F(int prev_level, int n)
    {
        if (n == 0) return 1;
        auto it = cache.find({prev_level, n});
        if (it != cache.end())
        {
            return it->second;
        }
        int count = 0;
        for (int level = 1; level < prev_level; level++)
        {
            if (n < level) break;
            count += F(level, n - level);
        }
        return cache[{prev_level, n}] = count;
    }

private:
    std::map<std::pair<int, int>, int> cache;
};

int main()
{
	int N;
	std::cin >> N;
    Solver solver;
    std::cout << solver.F(N + 1, N);
	return 0;
}