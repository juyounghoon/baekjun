#include <iostream>
#include <vector>

using namespace std;

#define MOD 1000000000

int N;
vector<int> StairNum;
vector<vector<int>> Ended; // [N][n]: 길이가 N인 계단수에서 n으로 끝나는 수의 개수
int main(){
    cin >> N;
    StairNum = vector<int>(N+1, 0);
    Ended = vector<vector<int>>(N+1, vector<int>(10));
    StairNum[1] = 9;
    Ended[1][0] = 0;
    for(int i = 1; i<=9; i++){
        Ended[1][i] = 1;
    }

    for(int i = 2; i<=N; i++){
        Ended[i][0] = Ended[i-1][1];
        for(int j = 1; j<=8; j++){
            Ended[i][j] = (Ended[i-1][j-1] + Ended[i-1][j+1]);
            Ended[i][j] %= MOD;
        }
        Ended[i][9] = Ended[i-1][8];
        Ended[i][9] %= MOD;

        for (int j = 0; j <= 9; j++) {
            StairNum[i] += Ended[i][j];
            StairNum[i] %= MOD;
        }
    }
    cout << StairNum[N]%MOD;

    return 0;
}