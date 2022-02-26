#include <iostream>
#include <vector>
#include <string>

struct User
{
    std::string name, value;
};

int Search(std::vector<struct User> users, std::string name)
{
    for (unsigned i = 0; i < users.size(); i++)
    {
        if (users[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    unsigned n;
    std::cin >> n;
    std::string command;
    std::vector<struct User> users;
    struct User user;
    for (unsigned i = 0; i < n; i++)
    {
        std::cin >> command >> user.name;
        int key = Search(users, user.name);
        if (command == "ADD")
        {
            std::cin >> user.value;
            if (key == -1)
            {
                users.push_back(user);
            }
            else
            {
                std::cout << "ERROR" << std::endl;
            }
        }
        if (command=="DELETE")
        {
            if (key==-1)
            {
                std::cout << "ERROR" << std::endl;
            }
            else
            {
                users.erase(users.begin() + key);
            }
        }
        if (command=="EDITPHONE")
        {
            std::cin >> user.value;
            if (key == -1)
            {
                std::cout << "ERROR" << std::endl;
            }
            else
            {
                users[key].value = user.value;
            }
        }
        if (command == "PRINT")
        {
            if (key == -1)
            {
                std::cout << "ERROR" << std::endl;
            }
            else
            {
                std::cout << users[key].name << " " << users[key].value << std::endl;
            }
        }
    }
    return 0;
}
