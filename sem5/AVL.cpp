#include <cstdio>
#include "AVL.h"

AVLNode::AVLNode(double _key) : key(_key)
{
    left = right = nullptr;
    height = 1;
}

int AVLNode::getBalanceFactor() const
{
    int r = (right == nullptr) ? 0 : right->height;
    int l = (left == nullptr) ? 0 : left->height;
    return r - l;
}

void AVLNode::fix()
{
    int r = (right == nullptr) ? 0 : right->height;
    int l = (left == nullptr) ? 0 : left->height;
    height = ((r > l) ? r : l) + 1;
}

AVLNode* AVLNode::rotateLeft()
{
    auto ret = right;
    right = ret->left;
    ret->left = this;
    fix();
    ret->fix();
    return ret;
}

AVLNode* AVLNode::rotateRight()
{
    auto ret = left;
    left = ret->right;
    ret->right = this;
    fix();
    ret->fix();
    return ret;
}

AVLNode* AVLNode::balance()
{
    fix();
    switch(getBalanceFactor())
    {
    case -2:
        if (left->getBalanceFactor() > 0)
            left = left->rotateLeft();
        return rotateRight();
    case 2:
        if (right->getBalanceFactor() < 0) 
            right = right->rotateRight();
        return rotateLeft();
    default:
        return this;
    }
}

AVLNode* AVLNode::insert(double _key)
{
    if (_key < key)
        left = (left == nullptr) ? new AVLNode(_key) : left->insert(_key);
    else
        right = (right == nullptr) ? new AVLNode(_key) : right->insert(_key);
    return balance();
}

AVLNode* AVLNode::findMinimum()
{
    return (left != nullptr) ? left->findMinimum() : this;
}  

AVLNode* AVLNode::removeMinimum()
{
    if (left == nullptr)
        return right;
    left = left->removeMinimum();
    return balance();
}

extern AVLNode* AVLNode::remove(AVLNode* p, double _key)
{
    if (p == nullptr)
        return nullptr;
    if (_key < p->key)
    {
        p->left = remove(p->left, _key);
        return p->balance();
    }
    else if (_key > p->key)
    {
        p->right = remove(p->right, _key);
        return p->balance();
    }
    else
    {
        AVLNode *l = p->left;
        AVLNode *r = p->right;
        delete p;
        if (r == nullptr)
            return l;
        AVLNode *min = r->findMinimum();
        min->right = r->removeMinimum();
        min->left = l;
        return min->balance();
    }
}

void AVLNode::print(int lev) const
{
    if (right != nullptr)
        right->print(lev + 1);
    for (int i = 0; i < lev; i++)
        printf("  ");
    printf("%.2f\n", key);
    if (left != nullptr)
        left->print(lev + 1);
}

AVLTree::AVLTree()
{
    root = nullptr;
}

bool AVLTree::insert(double _key)
{
    if (root == nullptr)
        root = new AVLNode(_key);
    else
        root = root->insert(_key);
    return true;
}

bool AVLTree::remove(double _key)
{
    root = AVLNode::remove(root, _key);
    return true;
}
    
void AVLTree::print() const
{
    if (root != nullptr)
        root->print(0);
    printf("\n");
}