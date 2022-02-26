#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <cassert>

typedef long long ll;

std::vector<ll> counter(const std::string& name)
{
	std::vector<ll> out(257);
	FILE* fin = fopen(name.c_str(), "rb");
	assert(fin != nullptr);
	for (int c = getc(fin); c != EOF; c = getc(fin))
	{
		out[c]++;
	}
	out[256]++; // Конец файла
	return out;
}

struct Node
{
	int sym = -1;
	ll freq = 0;
	Node* left = nullptr;
	Node* right = nullptr;
};

struct pq_less
{
	bool operator() (const Node* l, const Node* r)
	{
		return l->freq > r->freq;	
	}	
};

Node* build_tree(const std::vector<ll>& freqs)
{
	std::priority_queue<Node*, std::vector<Node*>, pq_less> pq;
	for (size_t l = 0; l < freqs.size(); l++)
	{
		if (freqs[l] == 0)
			continue;
		Node* n = new Node();
		n->sym = l;
		n->freq = freqs[l];
		pq.push(n);
	}

#if 0
	while(!pq.empty())
	{
		auto el = pq.top();
		pq.pop();
		printf("el: sym=%c freq=%lld\n", el->sym, el->freq);
	}

#endif
	while (pq.size() > 1)
	{
		auto el1 = pq.top();
		pq.pop();
		auto el2 = pq.top();
		pq.pop();
		auto par = new Node();
		par->left = el1;
		par->right = el2;
		par->sym = -1;
		par->freq = el1->freq + el2->freq;
		pq.push(par);
	}
	auto root = pq.top();
	pq.pop();
	return root;
}

void fill(const Node* root, std::vector<std::string>& codes, const std::string& s)
{
    if (root->left != nullptr)
	    fill(root->left, codes, s + "0");
    if (root->right != nullptr)
	    fill(root->right, codes, s + "1");
    if (root->sym >= 0)
    {
        codes[root->sym] = s;
    }
}

int main(int argc, char** argv)
{
	std::string name = (argc > 1) ? argv[1] : "input.txt";
	auto out = counter(name);
	auto root = build_tree(out);
	std::vector<std::string> codes(257);
	fill(root, codes, "");
   	for (int i = 0; i < 257; i++)
	{
        	if (codes[i].empty())
			continue;
        	printf("[%d]:%c = '%s'\n", i, i, codes[i].c_str());
    	}
	return 0;
}
