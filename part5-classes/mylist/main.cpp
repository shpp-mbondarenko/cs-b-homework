#include <iostream>
#include "mylist.h"
using namespace std;

int main()
{

    MyList<char>* li = new MyList<char>();
    li->push_back('f');
    li->push_back('h');
    li->push_back('j');
    li->push_back('g');
    li->insert('a', 3);
    cout << li->front() << endl;
    cout << "square breckets - " << (*li)[4] << endl;

        cout << li->front() << endl;
        li->pop_front();
        cout << li->front() << endl;
        li->pop_front();
        cout << li->front() << endl;
        li->pop_front();
        cout << li->front() << endl;
        li->pop_front();
        cout << li->front() << endl;
        li->pop_front();

    return 0;
}
