#include <iostream>
#include <algorithm>
#include <tuple>

struct Point
{
    long long x, y, z;
};

int main()
{
    size_t N;
    std::cin >> N;
    Point* points = new Point[N];
    for (size_t i = 0; i < N; i++)
    {
        std::cin >> points[i].x >> points[i].y >> points[i].z;
    }
    std::sort(points, points + N, [] (Point lhs, Point rhs) -> bool { return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z); });
    Point center = {(points[0].x + points[N - 1].x) / 2, (points[0].y + points[N - 1].y) / 2, (points[0].z + points[N - 1].z) / 2};
    for (size_t i = 1; i <= N / 2; i++)
    {
        if ((points[i].x + points[N - 1 - i].x) / 2 != center.x || (points[i].y + points[N - 1 - i].y) / 2 != center.y || (points[i].z + points[N - 1 - i].z) / 2 != center.z)
        {
            std::cout << "No";
            delete [] points;
            return 0;
        }
    }
    std::cout << "Yes";
    delete [] points;
    return 0;
}