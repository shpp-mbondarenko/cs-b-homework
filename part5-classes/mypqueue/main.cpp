#include <iostream>
#include "mypqueue.h"
using namespace std;
int main()
{
    PQueue<char, int>* pq = new PQueue<char, int>();

    pq->push('b', 7);
    pq->push('c', 8);
    pq->push('k', 2);
    pq->push('f', 5);
    pq->push('y', 4);


    cout << "First elem of Queue - " << pq->front() << endl;
    cout << "To string: " ;
    pq->toString();

    return 0;
}


//void push (T val, P cPri){
//    Node* tmp = new Node(val, cPri);
//    if(counter == 0){               //if we dont have elements
//        firstElem = tmp;
//        lastElem = tmp;
//    }else{
//        if(firstElem->priority < tmp->priority){
//            Node* b = firstElem;
//            b->prev = tmp;
//            tmp->next = b;
//            firstElem = tmp;
//        }else{
//            Node* curnode = firstElem;
//            while((tmp->priority)<(curnode->priority)){
//                Node* n = curnode->next;
//                if(n != 0){
//                    curnode = n;
//                    cout << "bla ";
//                }else{
//                    cout << "koo ";
//                    break;
//                }

//            }
//            if(curnode->next != 0){
//                Node* b = curnode->next;
//                tmp->next = b;
//                curnode->next = tmp;
//            }else{
//                Node* a = lastElem->prev;
//                Node* b = lastElem;
//                tmp->next = b;
//                tmp->prev = a;
//                a->next = tmp;
//            }
//        }
