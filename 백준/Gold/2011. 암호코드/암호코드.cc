#include <vector>
#include <iostream>

#define MOD 1000000

using namespace std;
vector<int> password;
vector<int> memo; // [n] : n자리 이하에서 나올 수 있는 해석의 수

int length = 0;

// DFS(현재 인덱스)
int DFS(int idx){
    if(password[idx] == 0){ // 0으로 시작하는 암호는 해석할 수 없음
        return 0;
    }
    else if(memo[idx] > 0){
        return memo[idx]%MOD;
    }
    else if(idx == length-1){// 마지막 인덱스 도달
        memo[idx] = 1;
        return memo[idx];
    }

    if(idx+1<=length-1 && password[idx] == 1 || (password[idx] == 2 && password[idx+1] <= 6)){ // 두 자리로 해석될 여지가 있는 경우
        memo[idx] += DFS(idx+1)%MOD; // 한 자리로 해석

        // 두 자리로 해석
        if(idx+1 == length-1){ // 두 자리로 해석되는데 마침 마지막 두 자리
            memo[idx]++;
        }
        else{
            memo[idx] += DFS(idx+2)%MOD;
        }
    }
    else{
        memo[idx] += DFS(idx+1)%MOD;
    }

    return memo[idx]%MOD;
}

int main(){
    string input;
    cin >> input;
    for(char i: input){
        password.push_back(i-'0');
        length++;
    }
    memo = vector<int>(length, 0);
    cout << DFS(0)%MOD << endl;

    return 0;
}