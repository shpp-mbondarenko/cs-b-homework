#include <iostream>
#include "myq.h"
using namespace std;
int main()
{
    Queue<char> qq;
    qq.push('c');
    qq.push('f');
    qq.push('g');
    cout << "Size of Queue - " << qq.size() << endl;
    cout << "First elem of Queue - " << qq.front() << endl;
    qq.pop();
    cout << "After pop first elem of Queue - " << qq.front() << endl;
    cout << "Size of Queue - " << qq.size() << endl;
    cout << "Last elem of Queue - " << qq.back() << endl;
//    qq.pop();
//    qq.pop();

    cout << "To string: " ;
    qq.toString();

    cout << "Privet!!!" << endl;
    return 0;
}
