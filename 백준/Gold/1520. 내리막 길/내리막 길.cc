#include <iostream>
#include <vector>

using namespace std;

//오 위 왼 아래
int dn[] = {0, -1, 0, 1};
int dm[] = {1, 0, -1, 0};

int N, M;
vector<vector<int>> map;
vector<vector<int>> memo;
vector<vector<bool>> isRoot;
vector<vector<bool>> isDone;
vector<vector<vector<pair<int, int>>>> heigher; // [n][m] 주변에서 보다 높은 위치 [n][m] = {[][], [][]}

int DP(int n, int m){
    if(n == 0 && m == 0) return 1;
    else if(isRoot[n][m]) return 0;
    else if(memo[n][m] != 0) return memo[n][m];
    else if(memo[n][m] == 0 && isDone[n][m]) return memo[n][m];

    for(auto h: heigher[n][m]){
        int next_n = h.first;
        int next_m = h.second;
        memo[n][m] += DP(next_n, next_m);
    }
    isDone[n][m] = true;
    return memo[n][m];
}

int main(){
    cin >> N >> M;
    map = vector<vector<int>>(N, vector<int>(M));
    memo = vector<vector<int>>(N, vector<int>(M));
    isRoot = vector<vector<bool>>(N, vector<bool>(M, false));
    isDone = vector<vector<bool>>(N, vector<bool>(M, false));
    heigher = vector<vector<vector<pair<int, int>>>>(N, vector<vector<pair<int, int>>>(M));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            cin >> map[i][j];
            memo[i][j] = 0;
        }
    }

    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            for(int k = 0; k<4; k++){
                int next_i = i+dn[k];
                int next_j = j+dm[k];
                if(next_i<0 || next_j<0 || next_i>=N || next_j>=M) continue;
                if(map[i][j] < map[next_i][next_j]){
                    heigher[i][j].push_back({next_i, next_j});
                }
            }
            if(heigher.size() == 0){
                isRoot[i][j] = true;
            }
        }
    }
    cout << DP(N-1, M-1);

    return 0;
}