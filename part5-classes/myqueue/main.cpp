#include <iostream>
#include "myq.h"
using namespace std;
int main()
{
    //tests
    //create and pop from empty queue
    Queue<char>* qqq = new Queue<char>();
    qqq->pop();

    //try to back() from empty queue
    qqq->back();

    //add elements in queue
    qqq->push('b');
    qqq->push('c');
    qqq->push('k');
    qqq->push('f');
    qqq->push('y');

    //get first element of queue
    cout << "First elem of Queue - " << qqq->front() << endl;

    //print queue
    cout << "To string: " ;
    qqq->toString();

    //delete one element and print queue
    cout << "To string: " ;
    qqq->pop();
    qqq->toString();

    //clear queue
    qqq->clear();
    qqq->toString();
    cout << endl;

    return 0;
}


