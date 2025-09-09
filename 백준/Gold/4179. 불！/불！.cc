#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 1000000

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int R, C;
vector<vector<char>> map;
vector<vector<int>> firemap; // 불이 번지는 속도를 표시한 map
vector<pair<int, int>> fires; // 불 최초 좌표
pair<int, int> jihun; // 지훈 최초 죄표
int ans;
bool isEscape;

int main(){
    ans = INF;
    isEscape = false;
    cin >> R >> C;
    map = vector<vector<char>>(R, vector<char>(C));
    firemap = vector<vector<int>>(R, vector<int>(C, INF));
    for(int i = 0; i<R; i++){
        for(int j = 0; j<C; j++){
            cin >> map[i][j];
            if(map[i][j] == 'F'){
                fires.push_back({i, j});
                firemap[i][j] = 0;
            }
            else if(map[i][j] == '#'){
                firemap[i][j] = INF;
            }
            else if(map[i][j] == 'J'){
                jihun = {i, j};
                map[i][j] = '.';
            }
        }
    }

    queue<vector<int>> q;
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    for(pair<int, int> fire: fires){
        q.push({fire.first, fire.second, 0});
        visited[fire.first][fire.second] = true;
    }
    while(!q.empty()){
        int curr_r = q.front()[0];
        int curr_c = q.front()[1];
        int curr_t = q.front()[2];
        q.pop();

        for(int i = 0; i<4; i++){
            int next_r = curr_r + dr[i];
            int next_c = curr_c + dc[i];
            if(next_r<0 || next_c<0 || next_r>=R || next_c>=C) continue;
            if(map[next_r][next_c] == '#' || visited[next_r][next_c]) continue;
            if(map[next_r][next_c] == '.' && curr_t+1 < firemap[next_r][next_c]){
                q.push({next_r, next_c, curr_t+1});
                firemap[next_r][next_c] = curr_t+1;
                visited[next_r][next_c] = true;
            }
        }
    }

    vector<vector<bool>> vis(R, vector<bool>(C, false));
    q.push({jihun.first, jihun.second, 0});
    vis[jihun.first][jihun.second] = true;
    while(!q.empty()){
        int curr_r = q.front()[0];
        int curr_c = q.front()[1];
        int curr_t = q.front()[2];
        q.pop();
        for(int i = 0; i<4; i++){
            int next_r = curr_r + dr[i];
            int next_c = curr_c + dc[i];
            if(next_r<0 || next_c<0 || next_r>=R || next_c>=C){
                // escape
                isEscape = true;
                if(curr_t+1<ans) ans = curr_t+1;
                break;
            }
            if(map[next_r][next_c] == '#' || vis[next_r][next_c]) continue;
            if(map[next_r][next_c] == '.' && curr_t+1 < firemap[next_r][next_c]){
                q.push({next_r, next_c, curr_t+1});
                vis[next_r][next_c] = true;
            }
        }
    }

    if(isEscape) cout << ans << "\n";
    else cout << "IMPOSSIBLE";

    return 0;
}