#include <iostream>
#include "mytree.h"
using namespace std;

int main()
{
    BSTree<int,int> a;
    a.insert(33, 4);
    a.insert(22, 5);
    a.insert(43, 2);
    a.insert(43, 1);
    a.insert(11, 3);
    a.insert(15, 6);
    a.insert(15, 8);
    a.insert(15, 7);
    a.insert(15, 10);
    a.insert(15, 14);
    a.insert(15, 15);
    a.insert(15, 16);
    a.insert(15, 17);
    a.remove(6);

    a.print();

    cout << "find 11 = " << a.find(3) <<endl;

    return 0;
}
