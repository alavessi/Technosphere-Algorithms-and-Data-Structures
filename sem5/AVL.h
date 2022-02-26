class AVLNode
{
private:
    AVLNode* left;
    AVLNode* right; 
    double key;
    int height;

public:
    AVLNode(double _key);
    int getBalanceFactor() const;
    void fix();
    AVLNode* rotateLeft();
    AVLNode* rotateRight();
    AVLNode* balance();
    AVLNode* insert(double _key);
    AVLNode* findMinimum(); 
    AVLNode* removeMinimum();
    static AVLNode* remove(AVLNode* p, double _key);
    void print(int lev) const;
};

class AVLTree
{
private:
    AVLNode* root;

public:
    AVLTree();
    bool insert(double _key);
    bool remove(double _key);
    void print() const;
};