#ifndef MYQ
#define MYQ
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

template <class T>
class Queue{
private:
    // create structure of node where we save value and pointer to next elem
    struct Node{
        T value;
        Node * next;
        Node (){}       //empty constructor
        Node (T val){
            value = val;
            next = 0;
        }
    };
    Node* firstElem;
    Node* lastElem;
    int counter;
public:
    //constructor
    Queue(){
        firstElem = 0;
        lastElem = 0;
        counter = 0;
    }
    ~Queue(){}

    //add value to Queue
    void push (T val){
        Node* tmp = new Node(val);
        if(counter == 0){
            firstElem = tmp;
            lastElem = tmp;
        }else{
            lastElem->next = tmp;
            lastElem = tmp;
        }
        counter++;
    }

    //return value of first element
    T front(){
          if(!empty()){
            return  firstElem->value;
        }else{
            std::cout << "You are trying to get element that not exists! Empty queue!" << std::endl;
        }
    }

    //delete first element
    T pop(){
        if(!empty()){
            Node* tmp = firstElem;
            firstElem = tmp->next;
            delete tmp;
            counter--;
        }else{
            std::cout << "You are trying to delete not exist element! Empty queue!" << std::endl;
        }
    }

    //return last element of Queue
    T back(){
        if(!empty()){
            return  lastElem->value;
        }else{
            std::cout << "You are trying to get element that not exists! Empty queue!" << std::endl;
        }
    }

    //size of Queue
    int size(){
        return counter;
    }

    void clear(){
        firstElem = 0;
        lastElem = 0;
        counter = 0;
    }

    //return true if Queue is empty
    bool empty(){
        return counter == 0;
    }

    //print Queue
    void toString(){
        if(!empty()){
            cout <<"{ ";
            Node * tmp = firstElem;
            while(tmp->next!=0){
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

#endif // MYQ

