#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

void UX(string &cmd, int &cur, vector<int> &prev){
    int x = stoi(cmd.substr(2)); // x칸 이동
    for(int i = 0; i<x; i++){
        cur = prev[cur];
    }
}

void DX(string &cmd, int &cur, vector<int> &next){
    int x = stoi(cmd.substr(2)); // x칸 이동
    for(int i = 0; i<x; i++){
        cur = next[cur];
    }
}

void C(int &n, int &cur, vector<int> &prev, vector<int> &next, stack<int> &deleted){
    deleted.push(cur);
    // 가장 마지막 행을 지우는 경우
    if(next[cur] == n){
        next[prev[cur]] = next[cur];
        cur = prev[cur];
        return;
    }
    // 가장 첫 행을 지우는 경우
    if(prev[cur] == -1){
        prev[next[cur]] = prev[cur];
        cur = next[cur];
        return;
    }

    prev[next[cur]] = prev[cur];
    next[prev[cur]] = next[cur];
    cur = next[cur];
}

void Z(int &n, vector<int> &prev, vector<int> &next, stack<int> &deleted){
    int restore = deleted.top();
    
    if(prev[restore] != -1){
        next[prev[restore]] = restore;
    }
    if(next[restore] != n){
        prev[next[restore]] = restore;
    }
    deleted.pop();
}

// n: 행의 개수, k: 처음 선택된 행의 위치(0~n-1), cmd: 수행한 명령어들이 담기 문자열
string solution(int n, int k, vector<string> cmd) {
    string answer(n, 'O');
    int current = k; // 현재 선택된 행 번호
    vector<int> prev(n);
    vector<int> next(n);
    stack<int> deleted; // 삭제된 행 번호를 넣을 스택
    
    for(int i = 0; i<n; i++){
        prev[i] = i-1;
        next[i] = i+1;
    }

    for(auto &c: cmd){
        switch (c[0]){
            case 'U':
                UX(c, current, prev);
                break;
            case 'D':
                DX(c, current, next);
                break;
            case 'C':
                C(n, current, prev, next, deleted);
                break;
            case 'Z':
                Z(n, prev, next, deleted);
                break;
            default:
                break;
        }
    }
    while(!deleted.empty()){
        answer[deleted.top()] = 'X';
        deleted.pop();
    }
    
    return answer;
}