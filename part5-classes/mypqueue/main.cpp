#include <iostream>
#include "mypqueue.h"
using namespace std;
int main()
{
    //tests
    //create and pop from empty queue
    PQueue<char, int>* pq = new PQueue<char, int>();
    pq->pop();

    //try to back() from empty queue
    pq->back();

    //add elements in queue
    pq->push('b', 7);
    pq->push('c', 8);
    pq->push('k', 2);
    pq->push('f', 5);
    pq->push('y', 4);

    //get first element of queue
    cout << "First elem of Queue - " << pq->front() << endl;

    //print queue
    cout << "To string: " ;
    pq->toString();

    //delete one element and print queue
    cout << "To string: " ;
    pq->pop();
    pq->toString();

    //clear queue
    pq->clear();
    pq->toString();
    cout << endl;

    return 0;
}



