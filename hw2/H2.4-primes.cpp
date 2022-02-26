#include <iostream>
#include <vector>

std::vector<bool> eratosthenes_sieve(size_t n)
{
    std::vector<bool> primes (n + 1, true);
    primes[0] = primes[1] = false;
    for (size_t i = 2; i * i <= n; i++)
    {
	    if (primes[i])
        {
		    for (size_t j = i * i; j <= n; j += i)
            {
			    primes[j] = false;
            }
        }
    }
    return primes;
}

int solution(const std::vector<bool>& primes, size_t N, size_t M)
{
    size_t count = 0;
    for (size_t i = 2; i < 2 + N; i++)
    {
        count += primes[i];
    }
    for (int K = 2; K <= 20000000; K++)
    {
        if (count == M)
        {
            return K;
        }
        count += primes[K + N] - primes[K];
    }
    return -1;
}

int main()
{
    size_t M, N;
    std::cin >> M >> N;
    std::vector<bool> primes = eratosthenes_sieve(N + 20000000);
    std::cout << solution(primes, N, M);
    return 0;
}