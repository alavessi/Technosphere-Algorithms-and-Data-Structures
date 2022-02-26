#include <stdio.h>
#include <assert.h>

class myset
{
public:
	enum {BITS = 8 * sizeof(size_t)};
	
	myset(size_t size): size(size)
	{
		storage = new size_t[(size + BITS - 1) / BITS];
	}

	~myset()
	{
		delete [] storage;
	}

	void insert(size_t elem)
	{
		assert(elem < size);
		storage[elem / BITS] |= ((size_t)1 << (elem % BITS));
	}

	void erase(size_t elem)
	{
		assert(elem < size);
		storage[elem / BITS] &= ~((size_t)1 << (elem % BITS));
	}

	bool in(size_t elem)
	{
		assert(elem < size);
		return (storage[elem / BITS] >> (elem % BITS)) & 1;
	}
	
private:
	size_t* storage = nullptr;
	size_t size;
};

int main()
{
	myset s(1000);
	for (size_t i = 0; i < 10; i++)
	{
		s.insert(i);
	}
	for (size_t i = 0; i < 20; i += 2)
	{
		if(s.in(i))
		{
			printf("%zu found\n", i);
		}
	}
	s.erase(5);
	if (s.in(5))
	{
		printf("OOPS: %zu must not be in set!\n", (size_t)5);
	}
}
