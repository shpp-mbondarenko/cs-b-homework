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
    int stSize;

    // increase vector's capacity twice and dublicate data to a new storage
    void enhance() {
        maxSize *= 2;
        T *newData = new T[maxSize];
        for (int i = 0; i < stSize; i++)
            newData[i] = stData[i];
        T *tmp = stData;
        stData = newData;
        delete tmp;
    }
    /**
     *Check if size of stack bigger or not the maxSize
     * @return - true if stSize >= maxSize
     */

    bool  notExceed() { return stSize >= maxSize; }

public:
    //constructor
    Stack(){
        maxSize = INI_STACK_SIZE;
        stData = new T[maxSize];
        stSize = 0;
    }
    ~Stack(){}

    // return stack size
    int size() const {
        return stSize;
    }

    // adds an element to the stack
    void push(T value) {
        if (notExceed()){
            enhance();
        }
        stData[stSize] = value;
        stSize++;

    }
    // returns top element of stack
    T top() {
        if(stSize != 0){
        return stData[stSize-1];
        }else{
            std::cout << "You are trying to get not exist value! Empty stack!" << std::endl;
        }
    }
    // removes element from stack
    void pop() {
        if(stSize != 0){
            stSize--;
        }else{
            std::cout << "You are trying to delete not exist value!" << std::endl;
//            exit (EXIT_FAILURE);
        }
    }

    //print stack
    void toString(){
        cout << "{ ";
        for(int i = 0; i < stSize; i++){
            cout << stData[i];
            if(i != stSize-1){
                cout <<", ";
            }
        }
        cout << " }" <<endl;
    }

    //return true if stack is empty
    bool isEmpty(){
        return stSize == 0;
    }
};



#endif // MYSTACK

