#include <iostream>
#include <string>

bool match(const std::string& sometext, const std::string& pattern, size_t i, size_t j)
{
    while (i < sometext.size() && j < pattern.size())
    {
        if (sometext[i] != pattern[j] && pattern[j] != '?')
        {
            if (pattern[j] == '*')
            {
                if (j + 1 == pattern.size()) return true;
                for (size_t k = i; k < sometext.size(); k++)
                {
                    if (match(sometext, pattern, k, j + 1)) return true;
                }
                return false;
            }
            else return false;
        }
        else
        {
            i++;
            j++;
        }
    }
    return i == sometext.size() && (j == pattern.size() || (j + 1 == pattern.size() && pattern[j] == '*'));
}

int main()
{
    std::string sometext, pattern;
    std::cin >> sometext >> pattern;
    if (match(sometext, pattern, 0, 0))
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
    return 0;
}