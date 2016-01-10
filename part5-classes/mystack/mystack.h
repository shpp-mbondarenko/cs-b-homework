#ifndef MYSTACK
#define MYSTACK
#include <iostream>
#include <stdlib.h>
#define INI_STACK_SIZE 8

using namespace std;

template <class T>
class Stack{
private:
    T *stData;
    int maxSize;
    int curSize;

    // increase vector's capacity twice and duplicate data to a new storage
    void enhance() {
        maxSize *= 2;
        T *newData = new T[maxSize];
        for (int i = 0; i < curSize; i++)
            newData[i] = stData[i];
        T *tmp = stData;
        stData = newData;
        delete tmp;
    }
    /**
     *Check if size of stack bigger or not the maxSize
     * @return - true if stSize >= maxSize
     */

    bool  notExceed() { return curSize >= maxSize; }

public:
    //constructor
    Stack(){
        maxSize = INI_STACK_SIZE;
        stData = new T[maxSize];
        curSize = 0;
    }
    ~Stack(){}

    // return stack size
    int size() const {
        return curSize;
    }

    // adds an element to the stack
    void push(T value) {
        if (notExceed()){
            enhance();
        }
        stData[curSize] = value;
        curSize++;

    }
    // returns top element of stack
    T top() {
        if(curSize != 0){
        return stData[curSize-1];
        }else{
            std::cout << "You are trying to get not exist value! Empty stack!" << std::endl;
        }
    }
    // removes element from stack
    void pop() {
        if(curSize != 0){
            curSize--;
        }else{
            std::cout << "You are trying to delete not exist value!" << std::endl;
//            exit (EXIT_FAILURE);
        }
    }

    //print stack
    void toString(){
        cout << "{ ";
        for(int i = 0; i < curSize; i++){
            cout << stData[i];
            if(i != curSize-1){
                cout <<", ";
            }
        }
        cout << " }" <<endl;
    }

    //return true if stack is empty
    bool isEmpty(){
        return curSize == 0;
    }
};



#endif // MYSTACK

