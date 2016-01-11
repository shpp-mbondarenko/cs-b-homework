#include <iostream>
#include "mystack.h"
using namespace std;

int main()
{
    //tests
    //create and pop from empty stack
    Stack<int> st;
    st.pop();

    //get element from empty stack
    st.top();

    //add elements
    st.push(1);    st.push(2);    st.push(3);    st.push(8);

    //get top element
    cout << st.top() << endl;

    //get size of stack
    cout << st.size() <<endl;

    //print stack
    st.toString();

    return 0;
}
