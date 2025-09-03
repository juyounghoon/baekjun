#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dn[] = {0, 1, 0, -1};
int dm[] = {1, 0, -1, 0};

int ans;
vector<vector<int>> A;
int N, L, R;

void Init_Parent(vector<vector<pair<int, int>>> &parent){
    parent = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>(N));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            parent[i][j] = {i, j};
        }
    }
}


void People_Move(vector<vector<pair<int, int>>> &parent){
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            bool flag = false;
            if(visited[i][j]) continue;
            vector<pair<int, int>> united;
            united.push_back({i, j});
            int people = 0;
            int cnt = 0;
            queue<pair<int, int>> q;
            q.push({i,j});
            while(!q.empty()){
                int curr_n = q.front().first;
                int curr_m = q.front().second;
                q.pop();
                for(int k = 0; k<4; k++){
                    int next_n = curr_n + dn[k];
                    int next_m = curr_m + dm[k];
                    if(next_n<0 || next_m<0 || next_n>=N || next_m>=N) continue;
                    if(visited[next_n][next_m]) continue;
                    if(parent[next_n][next_m] == parent[curr_n][curr_m]){
                        flag = true;
                        united.push_back({next_n, next_m});
                        q.push({next_n, next_m});
                        people += A[next_n][next_m];
                        cnt++;
                        visited[next_n][next_m] = true;
                    }
                }
            }
            if(!flag) continue;
            int united_people = people/cnt;
            for(pair<int, int> u: united){
                A[u.first][u.second] = united_people;
            }
        }
    }
}


int Diff(int a, int b){
    return a>b ? a-b : b-a;
}

void BFS(vector<vector<pair<int, int>>> &parent, bool &flag){
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            if(visited[i][j]) continue;
            queue<pair<int, int>> q;
            q.push({i,j});
            while(!q.empty()){
                int curr_n = q.front().first;
                int curr_m = q.front().second;
                q.pop();
                for(int k = 0; k<4; k++){
                    int next_n = curr_n + dn[k];
                    int next_m = curr_m + dm[k];
                    if(next_n<0 || next_m<0 || next_n>=N || next_m>=N) continue;
                    if(visited[next_n][next_m]) continue;
                    int diff = Diff(A[next_n][next_m], A[curr_n][curr_m]);
                    if(diff >= L && diff <= R){
                        flag = true;
                        q.push({next_n, next_m});
                        parent[next_n][next_m] = parent[curr_n][curr_m];
                        visited[next_n][next_m] = true;
                    }
                }
            }
        }
    }
}

int main(){
    cin >> N >> L >> R;
    ans = 0;
    A = vector<vector<int>>(N, vector<int>(N));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            cin >> A[i][j];
        }
    }
    vector<vector<pair<int, int>>> parent;
    bool flag = true;
    while(flag){
        flag = false;
        Init_Parent(parent);
        BFS(parent, flag);
        People_Move(parent);
        if(flag) ans++;
    }

    cout << ans << endl;
    return 0;
}