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
        Node* prew;
        Node (){
            value = 0;
            next = 0;
            prew = 0;
        }
        Node(T v) {
            value = v;
            next = 0;
            prew = 0;
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
    // overload opertor []
    T operator[](int i){
        Node* res = new Node();
        if(i <= counter){
            for(int y = 0; y < i; y++){
                if(y == 0){
                    res->value = head->value;
                    res->next = head ->next;
                    res->prew = head -> prew;
                }
                if(y != 0){
                    res->value = res->next->value;
                    res->next = res->next->next;
                }
            }
            return res->value;
        }else{
            std::cerr << "Error! Try get too hight index list (element not exist)." << std::endl;
            exit(EXIT_FAILURE);
        }
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
        if (empty()) {
            std::cerr << "Error! Try front() from empty list." << std::endl;
            exit(EXIT_FAILURE);
        }
        return head->value;
    }

    //return last element of list
    T back() {
        if (empty()){
            std::cerr << "Error! Try back() from empty list." << std::endl;
            exit(EXIT_FAILURE);
        }
        return tail->value;
    }

//insert nodein middle
    void insert(T val, int n = 0) {
        if(n >= counter){
            push_back(val);
        }
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
             t->prew = tmp->prew;
             t->next = tmp;
             tmp->prew = t;
             std::cout << "dada" << std::endl;
             delete t, tmp;
         }


    }

    //add to start of list
    void push_front(T value) {
        Node* newNode = new Node(value);
        if (empty()) {
            tail = newNode;
            head = newNode;
        } else {
            head->prew = newNode;
            newNode->next = head;
            head = newNode;
        }
        counter++;
          delete newNode;
    }

    //add to end of list
    void push_back(T value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prew = tail;
            tail = newNode;
        }
        counter++;
    }

    //delete first element in list
    void pop_front() {
        if (empty()) {
            std::cerr << "Error! Empty list." << std::endl;
            exit(EXIT_FAILURE);
        }
        Node* removedNode = head;
        if (size() > 1) {
            head = removedNode->next;
            head->prew = 0;
        } else {
            head = 0;
            tail = 0;
        }
        delete removedNode;
        counter--;
    }

    //delete element from tail
    void pop_back() {
        if (empty()) {
            std::cerr << "Error! Empty list." << std::endl;
            exit(EXIT_FAILURE);
        }
        Node* removedNode = tail;
        if (size() > 1) {
            tail = removedNode->prew;
            tail->next = 0;
        } else {
            tail = 0;
            head = 0;
        }
        delete removedNode;
        counter--;
    }

    void clear() {
        while(!empty())
            pop_back();
    }
};



#endif // MYLIST

