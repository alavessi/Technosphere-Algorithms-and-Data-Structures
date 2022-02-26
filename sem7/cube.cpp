#include <cstdio>
//#include <vector>
#include <unordered_map>

class Solver
{
public:
    double p(int n, int m)
    {
        if (n == 1)
        {
            if (m >= 1 && m <= 6)  return 1./6.; 
            else                   return 0.;
        }
        auto adapter = [] (int n, int m) -> int { return n * 10000 + m; };
        auto it = cache.find(adapter(n,m));
        if (it != cache.end())
        {
            return it->second;
        }
        double sum = 0.;
        for (int i = 1; i <= 6; i++)
        {
            sum += p(n - 1, m - i);
        }
        return cache[adapter(n, m)] = sum / 6.;
    
        /*std::vector<double> line1(6 * n + 1, 1./6.), line2(6 * n + 1, 0.);
        for (int iter = 1; iter < n; iter++)
        {
            for (int i = iter; i <= 6 * iter; i++)
            {
                for (int j = 1; j <= 6; j++)
                {
                    line2[i + j] += line1[i] / 6.;
                }
            }
            std::swap(line1, line2);
        }
        return line1[m];*/
    }

private:
    std::unordered_map<int, double> cache;
};

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    if (m < n || m > 6*n)
    {
        printf("0");
        return 0;
    }
    Solver solver;
    printf("%.10lf", solver.p(n, m));
}  
