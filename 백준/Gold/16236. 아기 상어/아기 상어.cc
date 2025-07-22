#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 위 왼 아 오
int dn[] = {-1, 0, 1, 0};
int dm[] = {0, -1, 0, 1};

int N; // map 크기
int t; // 시간
vector<vector<int>> map;
vector<int> fish; // [n] = 크기가 n인 물고기 수
typedef struct Shark{
    int size;
    int n, m;
    int eat;
}Shark;

// 다음 물고기를 찾는 함수
pair<pair<int, int>, int> Find_NextFish(vector<vector<int>> &map, Shark &shark){
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    pair<pair<int, int>, int> dest = {{-1, -1}, 100000};
    int d = 0;
    int n = shark.n;
    int m = shark.m;
    int fish_size = 0;
    bool flag_findfish = false;
    queue<pair<pair<int, int>, int>> q; // {n, m}, dist
    q.push({{n, m}, 0});
    visited[n][m] = true;
    while(!q.empty()){
        int curr_n = q.front().first.first;
        int curr_m = q.front().first.second;
        int curr_d = q.front().second;
        q.pop();
        for(int i = 0; i<4; i++){
            int next_n = curr_n + dn[i];
            int next_m = curr_m + dm[i];
            if(next_n<0 || next_m<0 || next_n>=N || next_m>=N || // map 밖이거나
                map[next_n][next_m] > shark.size || // 아기상어보다 더 큰 물고기거나
                visited[next_n][next_m]) continue; // 이미 방문한 곳
            else if(map[next_n][next_m]==0 || map[next_n][next_m]==shark.size){
                q.push({{next_n, next_m}, curr_d+1});
            }
            else if(map[next_n][next_m]>0 && map[next_n][next_m]<shark.size){
                flag_findfish = true;
                if(curr_d+1 < dest.second){
                    dest = {{next_n, next_m}, curr_d+1};
                    fish_size = map[next_n][next_m];
                }
                else if(curr_d+1 == dest.second && next_n<dest.first.first){
                    dest = {{next_n, next_m}, curr_d+1};
                    fish_size = map[next_n][next_m];
                }
                else if(curr_d+1 == dest.second && curr_n == dest.first.first && curr_m < dest.first.second){
                    dest = {{next_n, next_m}, curr_d+1};
                    fish_size = map[next_n][next_m];
                }
            }
            visited[next_n][next_m] = true;
        }
    }

    // map 갱신, 아기상어 위치 이동
    if(flag_findfish){
        map[shark.n][shark.m] = 0;
        map[dest.first.first][dest.first.second] = 9;
        shark.n = dest.first.first;
        shark.m = dest.first.second;
        fish[fish_size]--;
    }
    
    return dest;
}

bool isMoreFish(const vector<int> &fish, Shark shark){
    bool ret = false;
    int s = shark.size;
    for(int i = s-1; i>0; i--){
        if(fish[i]>0) return true;
    }
    return ret;
}

int main(){
    cin >> N;

    Shark shark;
    shark.size = 2;
    shark.eat = 0;

    map = vector<vector<int>>(N, vector<int>(N));
    fish = vector<int>(7, 0);
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            cin >> map[i][j];
            if(map[i][j] >= 1 && map[i][j] <= 6){
                fish[map[i][j]]++;
            }
            else if(map[i][j] == 9){
                shark.n = i;
                shark.m = j;
            }
        }
    }
    t = 0;
    while(isMoreFish(fish, shark)){
        pair<pair<int, int>, int> next = Find_NextFish(map, shark);
        if(next.first.first == -1){
            break;
        }
        t += next.second;
        shark.eat++;
        if(shark.eat == shark.size){
            shark.size++;
            shark.eat = 0;
        }
    }
    cout << t;

    return 0;
}
/*
1. 먹을 수 있는 물고기가 여러 마리면, 가장 가까운 물고기 먼저
    1-1. 같은 거리면 위에 있는 물고기 먼저
    1-2. 같은 거리, 같은 높이면 왼쪽 먼저
2. 2->3으로 크기가 커지려면 2마리를 먹어야 함. 3->4로 크기가 커지려면 3마리를 더 먹어야 함.
*/