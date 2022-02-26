#include <iostream>
#include <stdio.h>
#include <time.h>

typedef unsigned (*func)(unsigned);

unsigned bits1(unsigned limit) {
    unsigned res = 0;
    for (unsigned x = 0; x < limit; x++) {
        // Найти число битов в x.
        for (unsigned i = 1; i != 0; i += i) {
            if ((x & i) == i) res++;
        }
    }
    return res;
}

unsigned bits2(unsigned limit) {
    unsigned res = 0;
    for (unsigned x = 0; x < limit; x++) {
        // Найти число битов в x.
        for (unsigned t = x; t != 0; t >>= 1) {
            if (t & 1) res++;
        }
    }
    return res;
}

unsigned bits3(unsigned limit) {
    unsigned res = 0;
    for (unsigned x = 0; x < limit; x++) {
        // Найти число битов в x.
        for (unsigned t = x; t != 0; t >>= 1) {
            res += t & 1;                                                          
        }
    }
    return res;
}

unsigned bits4(unsigned limit) {
    unsigned res = 0;
    for (unsigned x = 0; x < limit; x++) {
        // Найти число битов в x.
        for (unsigned t = x; t != 0; t &= t - 1) {
            res++;
        }
    }
    return res;
}

unsigned bits5(unsigned limit) {
    unsigned res = 0;
    for (unsigned x = 0; x < limit; x++) {
        // Найти число битов в x.
        unsigned y = x;
        y = (y & 0x55555555) + ((y >> 1) & 0x55555555);
        y = (y & 0x33333333) + ((y >> 2) & 0x33333333);
        y = (y & 0x0F0F0F0F) + ((y >> 4) & 0x0F0F0F0F);
        y = (y & 0x00FF00FF) + ((y >> 8) & 0x00FF00FF);
        y = (y & 0x0000FFFF) + ((y >> 16) & 0x0000FFFF);
        res += y;
    }
    return res;
}

void bench(const char *name, func f, unsigned lim) {
    clock_t start = clock();
    unsigned r = f(lim);
    clock_t end = clock();
    printf("[%s]: r=%u time=%.3f\n", name, r, (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    const int CYCLES = 100000000;
    bench("bits1", bits1, CYCLES);
    bench("bits2", bits2, CYCLES);
    bench("bits3", bits3, CYCLES);
    bench("bits4", bits4, CYCLES);
    bench("bits5", bits5, CYCLES);
}

