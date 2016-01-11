#ifndef MYPQUEUE
#define MYPQUEUE
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

template <class T , class P>
class PQueue{
private:
    struct Node {
        T value;
        P priority;
        Node* next;
        Node* prev;
        Node(T v, P cPri){
            value = v;
            priority = cPri;
            next = 0;
            prev = 0;
        }
    };
    Node* firstElem;
    Node* lastElem;
    int counter;

public:
    PQueue() {
        firstElem = 0;
        lastElem = 0;
        counter = 0;
    }
    ~PQueue() {
        clear();
    }
    // return size of list
    int size() {
        return counter;
    }

    //if counter==0 return true
    bool empty() {
        return (size() == 0);
    }

    //first element return
    T front() {
        if(empty()){
            std::cout << "Error! Try front() from empty list." << std::endl;
        }
        return firstElem->value;
    }

    //return last element of list
    T back() {
        if(empty()){
            std::cout << "Error! Try back() from empty list." << std::endl;
        }else{
            return lastElem->value;
        }
    }

    //add to end of list
    void push(T value, P pri) {
        Node* tmp = new Node(value, pri);
        if(empty()){
            firstElem = tmp;
            lastElem = tmp;
            firstElem->next = lastElem;
            lastElem->prev = firstElem;
            lastElem->next = 0;
            counter++;
            return;
        }
        if(firstElem->priority < tmp->priority){
            Node* b = firstElem;
            tmp->next = b;
            tmp->prev = 0;
            firstElem = tmp;
            b->prev = tmp;
        }else{
            Node* curnode = firstElem;
            while(curnode->next != 0 && (curnode->next->priority) >= (tmp->priority)){
                curnode = curnode->next;
            }
            Node* h = curnode ->next;
            tmp->next = h;
            tmp->prev = curnode;
            curnode->next = tmp;
            if(h!=0){
                h -> prev = tmp;
            }
        }
        counter++;
    }

    //delete first element in list
    void pop() {
        if(empty()){
            std::cout << "Error! Empty queue." << std::endl;
            //            exit(EXIT_FAILURE);
        }else{
            Node* removedNode = firstElem;
            if(size() > 1){
                firstElem = removedNode->next;
                firstElem->prev = 0;
            }else{
                firstElem = 0;
                lastElem = 0;
            }
            delete removedNode;
            counter--;
        }
    }


    void clear() {
        while(!empty())
            pop();
    }
    //print Queue
    void toString(){
        if(!empty()){
            cout << counter  <<endl;
            cout <<"{ ";
            Node * tmp = firstElem;
            for(int i=1; i<counter; i++){
                cout << tmp->value;
                cout << ", ";
                tmp = tmp->next;
            }
            cout << tmp->value;
            cout << " }" << endl;
        }else{
            cout <<"{ }";
        }
    }

};

#endif // MYPQUEUE

