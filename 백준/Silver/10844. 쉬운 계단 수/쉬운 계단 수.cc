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
            StairNum[i] = (StairNum[i] + Ended[i][j]) % MOD;
        }
    }
    cout << StairNum[N]%MOD;

    return 0;
}
/*
 1 2 3 4 5 6 7 8 9 => 9, 0끝: 0, 9끝: 1
 10 12, 21 23, 32 34, 43 45, 54 56, 65 67, 76 78, 87 89, 98 => 9*2 - 1 = 17, 0끝: 1, 9끝: 1
 101, 121 123, 210 212, ... , 878 876, 898, 987 989 => 17*2 - 2
 0끝수[i] = 1끝수[i-1]
 1끝수[i] = 2끝수[i-1] + 0끝수[i-1]
 2[i] = 1[i-1] + 3[i-1]
 ...
 8[i] = 9[i-1] + 7[i-1]
 9끝수[i] = 8끝수[i-1]
 StairNum[N+1] = StairNum[N]*2 - 0끝수[i-1] - 9끝수[i-1]
 */