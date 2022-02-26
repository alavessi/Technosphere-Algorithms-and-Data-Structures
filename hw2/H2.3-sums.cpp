#include <iostream>
#include <vector>

int main()
{
	size_t N, Q;
	std::cin >> N >> Q;
	std::vector<int> a(N), b(N), changes(N + 1, 0);
	for (size_t i = 0; i < N; i++)
	{
		std::cin >> a[i];
	}
	for (size_t k = 0; k < Q; k++)
	{
		size_t L, R, X;
		std::cin >> L >> R >> X;
		changes[L] += X;
		changes[R + 1] -= X;	
	}
	b[0] = changes[0];
	for (size_t i = 1; i < N; i++)
	{
		b[i] = b[i-1] + changes[i];	
	}
	for (size_t i = 0; i < N; i++)
	{
		std::cout << a[i] + b[i] << " ";	
	}
	return 0;
}
