#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dn[] = {0, 1, 0, -1};
int dm[] = {1, 0, -1, 0};

int N, M;
int ans;
vector<vector<int>> map;

void PrintMap(const vector<vector<int>> &map){
    cout << "=====Print Map=====\n";
    for(int i = 0; i<=N+1; i++){
        for(int j = 0; j<=M+1; j++){
            cout << map[i][j];
        }
        cout << endl;
    }
}

int CountZero(const vector<vector<int>> &map){
    int cnt = 0;
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=M; j++){
            if(map[i][j] == 0) cnt++;
        }
    }
    return cnt;
}

void DiffVirus(vector<vector<int>> &map, vector<pair<int, int>> viruses){
    for(pair<int, int> virus: viruses){
        queue<pair<int, int>> q;
        q.push({virus.first, virus.second});
        while(!q.empty()){
            int curr_n = q.front().first;
            int curr_m = q.front().second;
            q.pop();

            for(int i = 0; i<4; i++){
                int next_n = curr_n + dn[i];
                int next_m = curr_m + dm[i];
                if(map[next_n][next_m] == 0){
                    map[next_n][next_m] = 2;
                    q.push({next_n, next_m});
                }
            }
        }
    }
}

void BuildWall(vector<vector<int>> map, vector<pair<int, int>> walls, vector<pair<int, int>> viruses){
    for(pair<int, int> wall: walls){
        map[wall.first][wall.second] = 1;
    }
    
    DiffVirus(map, viruses);
    int CntZero = CountZero(map);
    if(CntZero > ans) ans = CntZero;
}

int main(){
    ans = 0;
    cin >> N >> M;
    map = vector<vector<int>>(N+2, vector<int>(M+2, 1));
    vector<pair<int, int>> viruses;
    vector<pair<int, int>> zeros;
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=M; j++){
            int input; cin >> input;
            map[i][j] = input;
            if(input == 2) viruses.push_back({i, j});
            else if(input == 0) zeros.push_back({i, j});
        }
    }
    for(int i = 0; i<zeros.size(); i++){
        for(int j = i+1; j<zeros.size(); j++){
            for(int k = j+1; k<zeros.size(); k++){
                vector<pair<int, int>> walls;
                walls.push_back({zeros[i].first, zeros[i].second});
                walls.push_back({zeros[j].first, zeros[j].second});
                walls.push_back({zeros[k].first, zeros[k].second});
                BuildWall(map, walls, viruses);
            }
        }
    }
    cout << ans;
    return 0;
}