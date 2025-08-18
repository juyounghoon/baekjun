#include <iostream>
#include <vector>

#define MOD 9901

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> memo_empty(N+1, 0); // [n]: 맨 아래 칸이 비워진 경우
    vector<int> memo_left(N+1, 0); // [n]: 맨 아래 칸이 왼쪽이 채워진 경우
    vector<int> memo_right(N+1, 0); // [n]: 맨 아래 칸이 오른쪽이 채워진 경우
    
    // 초기화
    memo_empty[1] = 1;
    memo_left[1] = 1;
    memo_right[1] = 1;
    
    for(int i = 2; i<=N; i++){
        memo_empty[i] = (memo_empty[i-1] + memo_left[i-1] + memo_right[i-1])%MOD;
        memo_left[i] = (memo_empty[i-1] + memo_right[i-1])%MOD;
        memo_right[i] = (memo_empty[i-1] + memo_left[i-1])%MOD;
    }
    int ans = (memo_empty[N] + memo_left[N] + memo_right[N])%MOD;
    cout << ans;
}
/*
empty[n] = empty[n-1] + left[n-1] + right[n-1];
left[n] = empty[n-1] + right[n-1];
right[n] = empty[n-1] + left[n-1];
*/