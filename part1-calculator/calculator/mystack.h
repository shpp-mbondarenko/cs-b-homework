#ifndef MYSTACK
#define MYSTACK

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

template <class T>
class myStack{
private:
    // create structure of node where we save value and pointer to previous elem
    struct Node{
        T value;
        Node * previous;
        Node (){}       //empty constructor
        Node ( T val){
            value = val;
            previous = 0;
        }
    };
    Node* topElem;
    int counter;
    //return reference to previous node
    Node* retRef(myStack<T> a){
        Node* res;
        res = a.topElem->previous;
        return res;
    }

public:
    //swapping stacks
    void swap(myStack<T>& a){
        T val = this->top();
        Node* fir = new Node(val);
        fir->previous = this->topElem->previous;
        val = a.top();
        Node* sec = new Node(val);
        sec->previous = retRef(a);
        a.topElem = fir;
        this->topElem = sec;
        delete fir, sec;
    }
    //constructor
    myStack(){
        topElem = 0;
        counter = 0;
    }
    ~myStack(){}
    //add value to Queue
    void push (T val){
        Node* tmp = new Node(val);
        if(counter == 0){
            topElem = tmp;
        }else{
            tmp->previous = topElem;
            topElem = tmp;
        }
        counter++;
    }
    //return value of first element
    T peek(){
        return topElem->value;
    }
    //delete first elem
   T pop(){
       T res;
        if(!isEmpty()){
            res = topElem->value;
            Node* tmp = topElem;
            topElem = tmp->previous;
            delete tmp;
            counter--;
        }else{
            std::cout << "You are trying to delete not exist value! Program will close!" << std::endl;
            exit (EXIT_FAILURE);
        }
        return res;
    }

    //size of Queue
    int size(){
        return counter;
    }

    //return true if Queue is empty
    bool isEmpty(){
        return counter == 0;
    }
//print Queue
    void toString(){
        if(!isEmpty()){
            cout <<"{ ";
            Node * tmp = topElem;
            while(tmp->previous!=0){
                cout << tmp->value;
                cout << ", ";
                tmp = tmp->previous;
            }
            cout << tmp->value;
            cout << " }" << endl;
        }else{
            cout <<"{ }";
        }

    }

};

#endif // MYSTACK

