#include <iostream>
#include <vector>
#include <string>

struct Node
{
	Node* c[3]{nullptr, nullptr, nullptr};
	bool isTerminal{false};
			
};

Node* make_tree (const std::vector<std::string>& words)
{
	return nullptr;
}

bool check_tree (const Node* root , const std::string& sentence)
{
	return false;
}

int main()
{
	std::string sentence;
	getline(std::cin, sentence);
	std::vector<std::string> words;

	return 0;
}
