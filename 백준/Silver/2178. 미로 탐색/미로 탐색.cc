#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

// 오 아 왼 위
int dn[] = {0, 1, 0, -1};
int dm[] = {1, 0, -1, 0};

int N, M;
int ans;
vector<vector<int>> map;
vector<vector<bool>> visited;

int main(){
    cin >> N >> M;
    map = vector<vector<int>>(N, vector<int>(M));
    visited = vector<vector<bool>>(N, vector<bool>(M, false));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            scanf("%1d", &map[i][j]);
            //cin >> map[i][j];
        }
    }

    queue<pair<pair<int, int>, int>> q; // {{n, m}, d}
    q.push({{0, 0}, 1});
    while(!q.empty()){
        int curr_n = q.front().first.first;
        int curr_m = q.front().first.second;
        int curr_d = q.front().second;
        q.pop();
        for(int i = 0; i<4; i++){
            int next_n = curr_n + dn[i];
            int next_m = curr_m + dm[i];
            if(next_n<0 || next_m<0 || next_n>=N || next_m>=M || map[next_n][next_m] == 0 || visited[next_n][next_m]) continue;
            if(map[next_n][next_m] == 1){
                visited[next_n][next_m] = true;
                q.push({{next_n, next_m}, curr_d+1});
            }
            if(next_n == N-1 && next_m == M-1){
                cout << curr_d+1;
                return 0;
            }
        }
    }

    return 0;
}