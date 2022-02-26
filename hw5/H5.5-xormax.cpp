#include <cstdio>
#include <set>

const unsigned int limit = 1 << 31;

class Node
{
    friend class BitsTree;
private:
    unsigned int _key;
    Node* parent;
    Node* left;
    Node* right;
    bool isTerminal;

public:
    Node(bool is_terminal, Node* p, unsigned int key = 0);
};

Node::Node(bool is_terminal, Node* p, unsigned int key) : _key(key), parent(p), left(nullptr), right(nullptr), isTerminal(is_terminal) {}

class BitsTree
{
private:
    Node* root;

public:
    BitsTree();
    ~BitsTree();
    void insert(unsigned int key);
    void remove(unsigned int key);
    unsigned int find(unsigned int key) const;
};

BitsTree::BitsTree()
{
    root = new Node(false, nullptr);
}

BitsTree::~BitsTree()
{
    delete root;
}

void BitsTree::insert(unsigned int key)
{
    unsigned int n = limit;
    Node* p = root;
    while (n)
    {
        if (key & n)
        {
            if (p->right == nullptr)
            {
                p->right = (n == 1) ? new Node(true, p, key) : new Node(false, p);
            }
            p = p->right;
        }
        else
        {
            if (p->left == nullptr)
            {
                p->left = (n == 1) ? new Node(true, p, key) : new Node(false, p);
            }
            p = p->left;
        }
        n >>= 1;
    }
}

void BitsTree::remove(unsigned int key)
{
    unsigned int n = limit;
    Node* p = root;
    while (n)
    {
        p = (p->left == nullptr || (p->right != nullptr && key & n)) ? p->right : p->left;
        n >>= 1;
    }
    while (p != root && p->left == nullptr && p->right == nullptr)
    {
        Node* par = p->parent;
        bool del_left = par->left == p;
        delete p;
        p = par;
        if (del_left)
        {
            p->left = nullptr;
        }
        else
        {
            p->right = nullptr;
        }
        n = n ? (n << 1) : 1;
    }
}

unsigned int BitsTree::find(unsigned int key) const
{
    unsigned int n = limit;
    Node* p = root;
    while (n)
    {
        p = (p->left == nullptr || (p->right != nullptr && key & n)) ? p->right : p->left;
        n >>= 1;
    }
    return p->_key;
}

int main()
{
    unsigned int N;
    scanf("%u", &N);
    BitsTree tree;
    std::set<unsigned int> s;
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int command, value;
        scanf("%u %u", &command, &value);
        switch (command)
        {
        case 1:
            if (s.find(value) == s.end())
            {
                tree.insert(value);
                s.insert(value);
            }
            break;
        
        case 2:
            if (s.find(value) != s.end())
            {
                tree.remove(value);
                s.erase(value);
            }
            break;

        case 3:
            if (!s.empty())
            {
                printf("%u\n", tree.find(~value));
            }
            break;
        }
    }
    for (auto x : s)
    {
        tree.remove(x);
    }
    return 0;
}