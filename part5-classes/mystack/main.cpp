#include <iostream>
#include "mystack.h"
using namespace std;

int main()
{
    Stack<int> st;

    st.push(1);    /*st.push(2);    st.push(3);    st.push(4);
    st.push(1);    st.push(2);    st.push(3);    st.push(4);    st.push(45);*/

    cout << st.top() << endl;
    st.pop();
 st.pop();
    cout << st.size() <<endl;
    st.toString();


    return 0;
}
