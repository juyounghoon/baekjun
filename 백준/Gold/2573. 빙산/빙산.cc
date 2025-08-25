#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dn[] = {0, 1, 0, -1};
int dm[] = {1, 0, -1, 0};

int ans;
int N, M;
vector<vector<int>> map;

int CountGroup(){
    int cnt = 0;
    
    vector<vector<bool>> visited(N, vector<bool>(M, false));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            if(visited[i][j] || map[i][j] == 0) continue;
            else if(map[i][j]>0){
                cnt++;
                queue<pair<int, int>> q;
                q.push({i, j});
                while(!q.empty()){
                    int curr_n = q.front().first;
                    int curr_m = q.front().second;
                    q.pop();
                    for(int k = 0; k<4; k++){
                        int next_n = curr_n + dn[k];
                        int next_m = curr_m + dm[k];
                        if(next_n<0 || next_m<0 || next_n>=N || next_m>=M) continue;
                        else if(visited[next_n][next_m]) continue;
                        else if(map[next_n][next_m]>0){
                            q.push({next_n, next_m});
                            visited[next_n][next_m] = true;
                        }
                    }
                }
            }
        }
    }

    return cnt;
}

int MeltFunc(vector<vector<int>> beforemap, vector<vector<int>> &newmap){
    int cnt = 0; // 녹은 빙하의 수
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            int curr_n = i;
            int curr_m = j;
            if(beforemap[curr_n][curr_m] <= 0) continue;
            for(int k = 0; k<4; k++){
                int next_n = curr_n + dn[k];
                int next_m = curr_m + dm[k];
                if(next_n<0 || next_m<0 || next_n>=N || next_m>=M) continue;
                if(newmap[curr_n][curr_m]<=0) continue;
                if(beforemap[next_n][next_m] == 0)
                {
                    newmap[curr_n][curr_m]--;
                    cnt++;
                }
            }
        }
    }

    return cnt;
}

int main(){
    ans = 0;
    cin >> N >> M;
    map = vector<vector<int>>(N, vector<int>(M));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            cin >> map[i][j];
        }
    }

    while(CountGroup()<2){
        if(MeltFunc(map, map) == 0){
            ans = 0;
            break;
        }
        ans++;
    }
    cout << ans;

    return 0;
}