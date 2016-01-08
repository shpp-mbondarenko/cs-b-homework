#include <iostream>
#include "mylist.h"
using namespace std;

int main()
{
    //tests
    //create list
    MyList<char>* li = new MyList<char>();

    //get element from empty list
    li->front();
    li->back();

    //delete from empty list
    li->pop_back();
    li->pop_front();

    //add elements
    li->push_back('f');
    li->push_back('h');
    li->push_back('j');
    li->push_back('g');
    li->push_front('w');

    //insert element
    li->insert('a', 7);
    li->insert('z', 1);

    //test square brackets
    cout << "square breckets - " << (*li)[4] << endl;
    cout << "square breckets - " << (*li)[1] << endl;
    cout << "square breckets - " << (*li)[9] << endl;

    //clear list
    li->clear();

    return 0;
}
