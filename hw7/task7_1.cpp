#include <iostream>
#include <vector>

int count_pyramids(int n, int k, std::vector<std::vector<int>>& pyramids)
{
	if (n < 0 || k < 0) return 0;
	if (k == 1)	return n == 1;
	else if (n <= 2) return 1;
	if (pyramids[n][k] >= 0) return pyramids[n][k];
	pyramids[n][k] = count_pyramids(n, k - 1, pyramids) + count_pyramids(n - k, k - 1, pyramids);
	return pyramids[n][k];
}

int main()
{
	int N;
	std::cin >> N;
	std::vector<std::vector<int>> pyramids(N + 1, std::vector<int>(N + 1, -1));
	std::cout << count_pyramids(N, N, pyramids);
	return 0;
}
