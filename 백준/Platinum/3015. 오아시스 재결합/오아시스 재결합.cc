#include <iostream>
#include <stack>

using namespace std;

int N;
stack<pair<int, int> > stk; // <입력받은 수, pop하면서 사라질 때 ans에 더해지는 값>
long long ans = 0;
void Func(int t);

int main(){
    cin >> N;

    int input;
    for(int i = 0; i<N; i++){
        cin >> input;
        Func(input);
    }

    while(!stk.empty()){
        ans += stk.top().second - 1;
        stk.pop();
    }

    cout << ans;
    return 0;
}

void Func(int t){
    if(stk.empty()){
        stk.push(make_pair(t, 1));
    }
    else if(stk.top().first < t){
        ans += stk.top().second;
        stk.pop();
        Func(t);
    }
    else if(stk.top().first > t){
        stk.push(make_pair(t, 2));
    }
    else if(stk.top().first == t){
        int cnt = stk.top().second;
        cnt += 1;
        //cout << cnt << "\n";
        stk.push(make_pair(t, cnt));
    }
}