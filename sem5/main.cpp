#include "AVL.h"

int main()
{
    AVLTree t;
    t.insert(3);
    t.insert(1);
    t.insert(4);
    t.insert(2);
    t.insert(5);
    t.insert(9);
    t.print();
    
    t.remove(1);
    t.print();
    
    t.remove(2);
    t.print();
    return 0;
}
