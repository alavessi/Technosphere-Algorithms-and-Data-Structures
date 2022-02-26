#include <iostream>
#include <set>
#include <string>
#include <algorithm>

struct Attempt
{
    size_t id, score;
    std::string name;
};

bool operator< (const Attempt& lhs, const Attempt& rhs)
{
    return lhs.name < rhs.name;
}

int main()
{
    size_t M, N;
    std::cin >> M >> N;
    Attempt* attempts = new Attempt[N];
    for (size_t i = 0; i < N; i++)
    {
        std::string name;
        size_t score;
        std::cin >> name >> score;
        attempts[i].id = i;
        attempts[i].name = name;
        attempts[i].score = score;
    }
    std::sort(attempts, attempts + N, [] (const Attempt& lhs, const Attempt& rhs) -> bool { return lhs.score > rhs.score || (lhs.score == rhs.score && lhs.id < rhs.id); });
    for (size_t i = 0; i < N; i++)
    {
        attempts[i].id = i;
    }
    std::set<Attempt> ss;
    for (size_t i = 0; i < N; i++)
    {
        ss.insert(attempts[i]);
    }
    for (size_t i = 0; i < N; i++)
    {
        attempts[i] = {0, 0, ""};
    }
    for (Attempt a : ss)
    {
        attempts[a.id] = a;
    }
    for (size_t i = 0; i < N; i++)
    {
        if (attempts[i].name != "")
        {
            std::cout << attempts[i].name << '\n';
        }
    }
    delete [] attempts;
    return 0;
}