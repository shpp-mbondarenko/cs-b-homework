#include <iostream>
#include "mytree.h"
using namespace std;

int main()
{
    //tests

    //create BSTree. Delete from empty tree
    BSTree<int,int> a;
    cout << "Delete element from empty tree." << endl;
    a.remove(4);

    //Try to find something in empty tree
    cout << "Find element in empty tree." << endl;
    a.find(5);

    //add few elements in tree and print it
    a.insert(22, 5);
    a.insert(33, 4);
    a.insert(43, 2);
    a.insert(43, 1);
    a.insert(11, 3);
    a.insert(15, 6);
    a.insert(15, 8);
    a.print();

    //delete top element 4
    cout << "Delete element 4." << endl;
    a.remove(4);
    a.print();

    cout << "Find element with key 5." << endl;
    cout << a.find(5) << endl;

    cout << "Find key, that not exists:" << endl;
    cout << a.find(7) << endl;

    return 0;
}
