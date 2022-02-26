#include <stdio.h>

int main()
{
	size_t N;
	scanf("%zu", &N);
	size_t W[23];
	size_t total = 0;
	for (size_t i = 0; i < N; i++)
	{
		scanf("%zu", W + i);
		total += W[i];
	}
	size_t min = -1;
	size_t maxg = (size_t)1 << N;
	for (size_t g = 0; g < maxg; g++)
	{
	size_t mass = ;
		for (size_t bit = 0, t = g; t != 0; bit++, t >>= 1)
		{
			mass += ((t & 1)-1) & W[bit];
		}
		auto mass2 = total - mass ;
		auto delta = (mass2 > mass) ? (mass2 - mass) : (mass - mass2);
		if (delta < min)
		{
			min = delta;
		}
	}
	printf("%zu\n", min);
	return 0;
}

