#include <cstdio>
#include <algorithm>
#include <tuple>

struct Client
{
    size_t id, count;
    double x, y;
};

int main()
{
    size_t N;
    double R;
    scanf("%zu %lf", &N, &R);
    Client* clients = new Client[N];
    for (size_t i = 0; i < N; i++)
    {
        clients[i].id = i;
        clients[i].count = 0;
        scanf("%lf %lf", &clients[i].x, &clients[i].y);
    }
    std::sort(clients, clients + N, [] (const Client& lhs, const Client& rhs) -> bool { return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y); });
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = i + 1; j < N; j++)
        {
            if ((clients[i].x - clients[j].x) * (clients[i].x - clients[j].x) + (clients[i].y - clients[j].y) * (clients[i].y - clients[j].y) <= R * R)
            {
                clients[i].count++;
                clients[j].count++;
            }
            else if (clients[j].x - clients[i].x > R) break;
        }
    }
    std::sort(clients, clients + N, [] (const Client& lhs, const Client& rhs) -> bool { return std::tie(rhs.count, lhs.id) < std::tie(lhs.count, rhs.id); });
    size_t num = 0;
    for (size_t i = 0; i < N; i++)
    {
        num += (clients[i].count != 0);        
    }
    for (size_t i = 0; i < ((num < 10) ? num : 10); i++)
    {
        printf("%zu %zu\n", clients[i].id, clients[i].count);
    }
    delete [] clients;
    return 0;
}