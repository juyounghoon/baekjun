#include <iostream>
#include <stack>
using namespace std;

int N;
stack<int> stk;
string command;

void Command(string cmd, int x);
void Push(stack<int> &s, int x); // 정수 x를 스택에 넣는 연산
void Pop(stack<int> &s); // 스택에서 가장 위에 있는 정수를 빼고, 그 수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.
void Size(stack<int> &s); // 스택에 들어있는 정수의 개수를 출력한다.
void Empty(stack<int> &s); // 스택이 비어있으면 1, 아니면 0을 출력한다.
void Top(stack<int> &s); // 스택의 가장 위에 있는 정수를 출력한다. 만약 스택에 들어있는 정수가 없는 경우에는 -1을 출력한다.

int main(){
    cin >> N;
    string tmp;
    int t = 0;
    for(int i = 0; i<N; i++){
        cin >> tmp;
        if(tmp == "push"){
            cin >> t;
        }
        Command(tmp, t);
    }
    return 0;
}

void Command(string cmd, int x){
    if(cmd == "push"){
        Push(stk, x);
    }
    else if(cmd == "pop"){
        Pop(stk);
    }
    else if(cmd == "size"){
        Size(stk);
    }
    else if(cmd == "empty"){
        Empty(stk);
    }
    else if(cmd == "top"){
        Top(stk);
    }
    else{
        return;
    }
}

void Push(stack<int> &s, int x){
    s.push(x);
}

void Pop(stack<int> &s){
    if(s.empty()){
        cout << -1 << "\n";
        return;
    }
    cout << s.top() << "\n";
    s.pop();
}

void Size(stack<int> &s){
    cout << s.size() << "\n";
}

void Empty(stack<int> &s){
    if(s.empty()){
        cout << 1 << "\n";
        return;
    }
    cout << 0 << "\n";
}

void Top(stack<int> &s){
    if(s.empty()){
        cout << -1 <<"\n";
        return;
    }
    cout << s.top() << "\n";
}