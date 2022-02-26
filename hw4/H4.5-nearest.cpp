#include <cstdio>
#include <algorithm>
#include <cmath>
#include <tuple>

struct point
{
	int id;
    double x, y;
};

inline bool cmp_x(const point& a, const point& b)
{
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

inline bool cmp_y(const point& a, const point& b)
{
	return a.y < b.y;
}

double mindist;
int ansa, ansb;

inline void upd_ans(const point& a, const point& b)
{
	double dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + .0);
	if (std::make_tuple(dist, std::min(a.id, b.id), std::max(a.id, b.id)) <= std::make_tuple(mindist, std::min(ansa, ansb), std::max(ansa, ansb)))
    {
		mindist = dist;
        ansa = std::min(a.id, b.id);
        ansb = std::max(a.id, b.id);
    }
}

void rec (point* a, int l, int r)
{
	if (r - l <= 3)
    {
		for (int i = l; i <= r; i++)
        {
			for (int j = i + 1; j <= r; j++)
            {
				upd_ans(a[i], a[j]);
            }
        }
        std::sort(a + l, a + r + 1, &cmp_y);
		return;
	}
 
	int m = (l + r) >> 1;
    double midx = a[m].x;
	rec(a, l, m);
    rec(a, m + 1, r);
	static point t[500000];
	std::merge(a + l, a + m + 1, a + m + 1, a + r + 1, t, &cmp_y);
	std::copy(t, t + r - l + 1, a + l);
 
	int tsz = 0;
	for (int i = l; i <= r; i++)
    {
		if (abs (a[i].x - midx) < mindist)
        {
			for (int j = tsz - 1; j >= 0 && a[i].y - t[j].y < mindist; j--)
            {
				upd_ans(a[i], t[j]);
            }
            t[tsz++] = a[i];
		}
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    point* a = new point[N];
    for (int i = 0; i < N; i++)
    {
        double x, y;
        scanf("%lf %lf", &x, &y);
        a[i].id = i + 1;
        a[i].x = x;
        a[i].y = y;
    }
    std::sort(a, a + N, &cmp_x);
    mindist = 1E20;
    rec(a, 0, N - 1);
    printf("%.10f %d %d", mindist, ansa, ansb);
    delete [] a;
    return 0;
}