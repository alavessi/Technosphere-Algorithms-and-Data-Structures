#include <iostream>
#include <set>
#include <map>
#include <utility>

typedef std::pair<size_t, size_t> coordinates;

int main()
{
    size_t N, M, L, K;
    std::cin >> N >> M >> L >> K;
    std::set<coordinates> alive;
    for (size_t i = 0; i < L; i++)
    {
        size_t x, y;
        std::cin >> x >> y;
        alive.insert(std::make_pair(x, y)); 
    }
    for (size_t i = 0; i < K; i++)
    {
        std::map<coordinates, size_t> neighbours;
        for (auto cell : alive)
        {
            if (cell.first && cell.second)
                neighbours[std::make_pair(cell.first - 1, cell.second - 1)]++;

            if (cell.first)
                neighbours[std::make_pair(cell.first - 1, cell.second)]++;

            if (cell.second)
                neighbours[std::make_pair(cell.first, cell.second - 1)]++;
            
            if (cell.first && cell.second < M - 1)
                neighbours[std::make_pair(cell.first - 1, cell.second + 1)]++;

            if (cell.first < N - 1 && cell.second)
                neighbours[std::make_pair(cell.first + 1, cell.second - 1)]++;

            if (cell.first < N - 1)
                neighbours[std::make_pair(cell.first + 1, cell.second)]++;

            if (cell.second < M - 1)
                neighbours[std::make_pair(cell.first, cell.second + 1)]++;

            if (cell.first < N - 1 && cell.second < M - 1)
                neighbours[std::make_pair(cell.first + 1, cell.second + 1)]++;
        }
        for (auto it = alive.begin(); it != alive.end(); it = (neighbours[*it] != 2 && neighbours[*it] != 3) ? alive.erase(it) : std::next(it));
        for (auto [coordinates, count]: neighbours)
        {
            if (count == 3)
            {
                alive.insert(coordinates);
            } 
        }
    }
    for (auto cell : alive)
    {
        std::cout << cell.first << " " << cell.second << "\n";
    }
    return 0;
}