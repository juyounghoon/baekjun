#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dn[] = {0, 1, 0, -1};
int dm[] = {1, 0, -1, 0};

int N, M;
int blank; // 최초 빈 칸 수
int ans = -1;
vector<vector<int>> map;
vector<pair<int, int>> viruses;

int MaxTime(const vector<vector<int>> &map){
    int time = 0;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            if(map[i][j]>time) time = map[i][j];
        }
    }
    return time;
}

int CountClean(vector<vector<int>> map){ // 바이러스가 안퍼진 공간 카운트
    int cnt = 0;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            if(map[i][j] == 0) cnt++;
        }
    }
    return cnt;
}

int BFS(vector<int> actives, vector<vector<int>> tmpmap){
    if(blank == 0) return 0;

    int spread = 0; // 새롭게 감염시킨 칸 수
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            if(map[i][j] == 0) tmpmap[i][j] = map[i][j]; // 빈칸
            else if(map[i][j] == 1) tmpmap[i][j] = -3; // 벽
            else if(map[i][j] == 2) tmpmap[i][j] = -1; // 비활성화 바이러스
        }
    }
    
    queue<vector<int>> q; // {n, m, day}
    for(int idx: actives){
        tmpmap[viruses[idx].first][viruses[idx].second] = -2; // 활성화 바이러스
        q.push({viruses[idx].first, viruses[idx].second, 0});
    }

    while(!q.empty()){
        int curr_n = q.front()[0];
        int curr_m = q.front()[1];
        int curr_d = q.front()[2];
        q.pop();
        if(spread == blank) break;

        for(int i = 0; i<4; i++){
            int next_n = curr_n+dn[i];
            int next_m = curr_m+dm[i];
            int next_d = curr_d + 1;

            if(next_n<0 || next_m<0 || next_n>=N || next_m>=N) continue;
            if(tmpmap[next_n][next_m] == -2 || tmpmap[next_n][next_m] == -3) continue;
            
            if(tmpmap[next_n][next_m] == 0){
                spread++;
                tmpmap[next_n][next_m] = next_d;
                q.push({next_n, next_m, next_d});
            }
            else if(tmpmap[next_n][next_m] == -1){
                tmpmap[next_n][next_m] = next_d;
                q.push({next_n, next_m, next_d});
            }
            else if(tmpmap[next_n][next_m]>next_d){
                tmpmap[next_n][next_m] = next_d;
                q.push({next_n, next_m, next_d});
            }
        }
    }
    if(spread < blank){
        return -1;
    }

    return MaxTime(tmpmap);
}

void DFS(int idx, vector<int> &actives){
    if(actives.size() == M){
        int count = BFS(actives, map);
        if(count >= 0 && count < ans || ans == -1){
            ans = count;
        }
        return;
    }
    for(int i = idx; i<viruses.size(); i++){
        actives.push_back(i);
        DFS(i+1, actives);
        actives.pop_back();
    }
}

int main(){
    cin >> N >> M;
    blank = 0;
    map = vector<vector<int>>(N, vector<int>(N));
    vector<int> actives; // 활성 바이러스 배열
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            cin >> map[i][j];
            if(map[i][j] == 2){
                viruses.push_back({i, j});
            }
            else if(map[i][j] == 0){
                blank++;
            }
        }
    }

    DFS(0, actives);

    cout << ans;
    return 0;
}
/*
2: 바이러스
활성 바이러스는 모든 칸으로 복제
*/