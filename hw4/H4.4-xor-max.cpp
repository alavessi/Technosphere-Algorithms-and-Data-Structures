#include <stdio.h>
#include <climits>
#include <algorithm>

void build_xor(int* t, int* a, unsigned v, unsigned tl, unsigned tr)
{
	if (tl == tr)
    {
		t[v] = a[tl];
    }
    else
    {
		unsigned tm = (tl + tr) >> 1;
		build_xor(t, a, v << 1, tl, tm);
		build_xor(t, a, (v << 1) + 1, tm + 1, tr);
		t[v] = t[v << 1] ^ t[(v << 1) + 1];
	}
}

void build_max(int* t, int* a, unsigned v, unsigned tl, unsigned tr)
{
	if (tl == tr)
    {
		t[v] = a[tl];
    }
    else
    {
		unsigned tm = (tl + tr) >> 1;
		build_max(t, a, v << 1, tl, tm);
		build_max(t, a, (v << 1) + 1, tm + 1, tr);
		t[v] = std::max(t[v << 1], t[(v << 1) + 1]);
	}
}

int Xor(int* t, unsigned v, unsigned tl, unsigned tr, unsigned l, unsigned r)
{
	if (l > r)
		return 0;
	if (l == tl && r == tr)
		return t[v];
	unsigned tm = (tl + tr) >> 1;
	return Xor(t, v << 1, tl, tm, l, std::min(r, tm)) ^ Xor(t, (v << 1) + 1, tm + 1, tr, std::max(l, tm + 1), r);
}

int max(int* t, unsigned v, unsigned tl, unsigned tr, unsigned l, unsigned r)
{
	if (l > r)
		return INT_MIN;
	if (l == tl && r == tr)
		return t[v];
	unsigned tm = (tl + tr) >> 1;
	return std::max(max(t, v << 1, tl, tm, l, std::min(r, tm)), max(t, (v << 1) + 1, tm + 1, tr, std::max(l, tm + 1), r));
}

void update_xor(int* t, unsigned v, unsigned tl, unsigned tr, unsigned pos, int new_val)
{
	if (tl == tr)
		t[v] = new_val;
	else
    {
		unsigned tm = (tl + tr) >> 1;
		if (pos <= tm)
			update_xor(t, v << 1, tl, tm, pos, new_val);
		else
			update_xor(t, (v << 1) + 1, tm + 1, tr, pos, new_val);
		t[v] = t[v << 1] ^ t[(v << 1) + 1];
	}
}

void update_max(int* t, unsigned v, unsigned tl, unsigned tr, unsigned pos, int new_val)
{
	if (tl == tr)
		t[v] = new_val;
	else
    {
		unsigned tm = (tl + tr) >> 1;
		if (pos <= tm)
			update_max(t, v << 1, tl, tm, pos, new_val);
		else
			update_max(t, (v << 1) + 1, tm + 1, tr, pos, new_val);
		t[v] = std::max(t[v << 1], t[(v << 1) + 1]);
	}
}

int main()
{
    size_t N, M;
    scanf("%zu %zu", &N, &M);
    int* a = new int[N];
    for (size_t i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }
    int* XOR = new int[4 * N];
    int* MAX = new int[4 * N];
    build_xor(XOR, a, 1, 0, N - 1);
    build_max(MAX, a, 1, 0, N - 1);
    for(size_t i = 0; i < M; i++)
    {
        unsigned code;
        scanf("%u", &code);
        if (code == 3)
        {
            size_t pos;
            int new_val;
            scanf("%zu %d", &pos, &new_val);
            update_xor(XOR, 1, 0, N - 1, pos, new_val);
            update_max(MAX, 1, 0, N - 1, pos, new_val);        
        }
        else
        {
            size_t L, R;
            scanf("%zu %zu", &L, &R);
            if (code == 1)
            {
                printf("%d\n", Xor(XOR, 1, 0, N - 1, L, R));
            }
            if (code == 2)
            {
                printf("%d\n", max(MAX, 1, 0, N - 1, L, R));
            }     
        }
    }
    delete [] a;
    delete [] XOR;
    delete [] MAX;
    return 0;
}