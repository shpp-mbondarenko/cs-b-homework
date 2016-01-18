#ifndef MYLIST
#define MYLIST

#include <iostream>
#include <string>
#include "stdlib.h"

template <class T>
class MyList {

private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
        Node () {
            value = 0;
            next = 0;
            prev = 0;
        }
        Node(T v) {
            value = v;
            next = 0;
            prev = 0;
        }
    };
    Node* head;
    Node* tail;
    int counter;

public:
    MyList() {
        head = 0;
        tail = 0;
        counter = 0;
    }
    ~MyList() {
        clear();
    }
    // overload operator []
    T operator[](int i) {
        Node* res = new Node();
        if(i <= counter){
            for(int y = 0; y < i; y++){
                if(y == 0){
                    res->value = head->value;
                    res->next = head->next;
                    res->prev = head->prev;
                }
                if(y != 0){
                    res->value = res->next->value;
                    res->next = res->next->next;
                }
            }
            return res->value;
        }else{
            cout << "Error! Try get too high index list (element not exist)." << endl;
            return NULL;
        }
    }

    // return size of list
    int size() {
        return counter;
    }

    //if counter == 0 return true
    bool empty() {
        return (size() == 0);
    }

    //first element return
    T front() {
        if (empty()){
            cout << "Error! Try front() from empty list." << endl;
        }else{
            return head->value;
        }
    }

    //return last element of list
    T back() {
        if(empty()){
            cout << "Error! Try back() from empty list." << endl;
        }else{
            return tail->value;
        }
    }

    //insert node in middle
    void insert(T val, int n = 0) {
        if(n >= counter){
            push_back(val);
        }else{
            if(n == 0){
                push_front(val);
            }else{
                Node* t = new Node(val);
                int c = 0;
                Node* tmp = head;
                while(c < n){
                    tmp = tmp->next;
                    c++;
                }
                t->prev = tmp->prev;
                t->next = tmp;
                tmp->prev = t;
            }
        }
    }

    //add to start of list
    void push_front(T value) {
        Node* newNode = new Node(value);
        if(empty()){
            tail = newNode;
            head = newNode;
        }else{
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        counter++;
    }

    //add to end of list
    void push_back(T value) {
        Node* newNode = new Node(value);
        if(empty()){
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        counter++;
    }

    //delete first element in list
    void pop_front() {
        if(empty()){
            cout << "Try to pop_front. Error! Empty list." << endl;
        }else{
            Node* removedNode = head;
            if(size() > 1){
                head = removedNode->next;
                head->prev = 0;
            }else{
                head = 0;
                tail = 0;
            }
            delete removedNode;
            counter--;
        }
    }

    //delete element from tail
    void pop_back() {
        if(empty()){
            cout << "Try to pop_back. Error! Empty list." << endl;
        }else{
            Node* removedNode = tail;
            if (size() > 1){
                tail = removedNode->prev;
                tail->next = 0;
            }else{
                tail = 0;
                head = 0;
            }
            delete removedNode;
            counter--;
        }
    }

    void clear() {
        while(!empty())
            pop_back();
    }
};



#endif // MYLIST

