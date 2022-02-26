#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <cassert>
#include <ctime>

template<typename T>
class CRCCoder
{
public:
    CRCCoder()
    {
        init();
    }

    static T calc(const void* data, unsigned size)
    {
        initTable();
        const unsigned char* p = reinterpret_cast<const unsigned char*>(data);
        T ctmp = T(-1);
#if 0
        while (size > 4)
        {
            ctmp ^= (T)(p[0]);
            ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
            ctmp ^= (T)(p[1]);
            ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
            ctmp ^= (T)(p[2]);
            ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
            ctmp ^= (T)(p[3]);
            ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
            p += 4;
            size -= 4;
        }
#endif
        while (size)
        {
            ctmp ^= (T)(p[0]);
            ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
            p++;
            size--;
        }
        return ctmp ^ T(-1);
    }

    static T calc(const char* p)
    {
        T ctmp = T(-1);
        while (*p)
        {
            ctmp ^= (T)(p[0]);
            ctmp = (ctmp >> 8) ^ _table[ctmp & 0xFF];
            p++;
        }
        return ctmp ^ T(-1);
    }

    void init()
    {
        initTable();
        _value = T(-1);
    }

    void update(unsigned char p)
    {
        _value ^= (T)(p);
        _value = (_value >> 8) ^ _table[_value & 0xFF];
    }

    T final()
    {
        return _value ^ T(-1);
    }

private:
    T _value;
    static T _table[256];
    static T POLY;
    static void initTable()
    {
        if (_table[0] == 0)
        {
            T *p = _table;
            int i, j;
            for (j = 0; j < 256; j++)
            {
                T x = j;
                for (i = 0; i < 8; i++)
                {
                    if ((x & 1) != 0)
                    {
                        x = (x >> 1) ^ POLY;
                    }
                    else
                    {
                        x = (x >> 1);
                    }
                }
                *p++ = x;
            }
        }
    }
};

template<> unsigned long long CRCCoder<unsigned long long>::POLY = 0xC96C5795D7870F42ULL;
template<> unsigned CRCCoder<unsigned>::POLY = 0xEDB88320U;
template<> unsigned long long CRCCoder<unsigned long long>::_table[256] = { 0 };
template<> unsigned CRCCoder<unsigned>::_table[256] = { 0 };


static unsigned long long  primes[] = {
    1009, 2011, 4013, 8017, 16001, 32003, 64007, 128021, 256019, 512009, 1000003, 1400017, 2000003, 2800001, 4000037,
    6000011, 8000009, 10000019, 13000027, 16000057, 20000003, 25000009, 30000001, 40000003, 50000017, 60000011,
    70000027, 80000023, 90000049, 100000007, 110000017, 120000007, 130000001, 200000033, 300000007, 400000009, 500000003,
    600000001, 700000001, 800000011, 900000011, 1000000007};

template <typename T, typename HASH, typename REHASH>
struct hash_table
{
    enum status { EMPTY, OCCUPIED, DELETED };
    struct hash_item
    {
        T key{};
        enum status stat = EMPTY;
    };
    std::vector<hash_item> data;
    size_t compares = 0;
    size_t occupied = 0;

    hash_table(size_t size)
    {
#if 1
        if (size < primes[0])
        {
            size = primes[0];
        }
        else
        {
            for (size_t i = 1; i < sizeof primes / sizeof primes[0]; i++)
            {
                if (size >= primes[i - 1] && size < primes[i])
                {
                   size = primes[i];
                   break;
                }
            }
        }
#endif
        data.resize(size);
    }
    ~hash_table()
    {
        printf("compares=%zu ocuppied=%zu\n", compares, occupied);
    }

    void rebuild()
    {
        printf("rebuild!\n");
        occupied = 0;
        std::vector<hash_item> new_data(data.size() * 3 / 2);
        for (auto const &ks: data)
        {
            if (ks.stat == OCCUPIED)
            {
                internal_insert(ks.key, new_data);
            }
        }
        std::swap(data, new_data);
    }

    bool insert(const T& key)
    {
        if (occupied + occupied >= data.size())
        {
           rebuild();
        }
        return internal_insert(key, data);
    }

    bool internal_insert(const T& key, std::vector<hash_item>& d)
    {
        size_t h = HASH()(key) % d.size();
        size_t s = REHASH()(key);
        for (;;h = (h + s) % d.size())
        {
            if (d[h].stat == OCCUPIED)
            {
                compares++;
                if (d[h].key == key) return false;
                continue;
            }
            if (d[h].stat != OCCUPIED)
            {
                occupied += d[h].stat == EMPTY;
                d[h].stat = OCCUPIED;
                d[h].key = key;
                return true;
            }
        }
        return true;
    }

    bool find(const T& key)
    {
        size_t h = HASH()(key) % data.size();
        size_t s = REHASH()(key);                                                               
        for (;;h = (h + s) % data.size())
        {
            if (data[h].stat == EMPTY) return false;
            if (data[h].stat == DELETED) continue; 
            compares++;
            if (data[h].key == key) return true;
        }
        return true;
    }

    bool erase(const T& key)
    {
        size_t h = HASH()(key) % data.size();
        size_t s = REHASH()(key);
        for (;;h = (h + s) % data.size())
        {
            if (data[h].stat == EMPTY) return false;
            if (data[h].stat == DELETED) continue; 
            compares++;
            if (data[h].key == key)
            {
                data[h].stat = DELETED;
                return true;
            }
        }
        return true;
    }
};

struct h1
{
    size_t operator()(const std::string& k)
    {
        size_t ret = 0;
        for (auto c: k)
        {
            ret += c;
        }
        return ret;
    }
};

struct h2
{
    size_t operator()(const std::string& k)
    {
        size_t ret = 0;
        for (auto c: k)
        {
            ret *= 8;
            ret += c;
        }
        return ret;
    }
};

struct h3
{
    size_t operator()(const std::string& k)
    {
        size_t ret = 0;
        for (auto c: k)
        {
            ret *= 29;
            ret += c - 'a' + 1;
        }
        return ret;
    }
};

struct h4
{
    size_t operator()(const std::string& k)
    {
        size_t ret = 0;
        for (auto c: k)
        {
            ret *= 259;
            ret += c;
        }
        return ret;
    }
};

CRCCoder<unsigned long long> crccoder;

struct h5
{
    size_t operator()(const std::string& k)
    {
        return crccoder.calc(k.c_str());
    }
};

struct h8
{
    size_t operator()(const std::string& k)
    {
        return 1;
    }
};

int main()
{
    const int KEYS = 100000;
    std::vector<std::string> tests(KEYS);
    for (int i = 0; i < KEYS; i++)
    {
        size_t len = 1 + rand() % 50;
        std::string s;
        for (size_t j = 0; j < len; j++)
        {
            s += 'a' + rand() % 26;
        }
        tests[i] = s;
    }
    // for (auto z: tests) printf("%s\n", z.c_str());
    hash_table<std::string, h5, h4> ht(109);
    for (const auto& k: tests)
    {
        ht.insert(k);
    }
    bool ok = true;
    for (const auto& k: tests)
    {
        ok &= ht.find(k);
    }
    assert(ok);
    for (const auto& k: tests)
    {
        ht.erase(k);
    }
}
