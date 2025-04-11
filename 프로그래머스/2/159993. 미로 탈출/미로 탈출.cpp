#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

int solution(vector<string> maps) {
    int answer = 0;
    
    int N = maps.size(); // maps의 세로 길이
    int M = maps[0].size(); // maps의 가로 길이
    vector<vector<char>> map(N+2, vector<char>(M+2)); // 주어진 maps의 둘레를 X로 감싼 새로운 맵
    for(int i = 0; i<N+2; i++){
        for(int j = 0; j<M+2; j++){
            if(i==0 || i==N+1 || j==0 || j==M+1){
                map[i][j] = 'X';
            }
            else{
                map[i][j] = maps[i-1][j-1];
            }
        }
    }
    
    pair<int, int> start; // S 좌표
    pair<int, int> end; // E 좌표
    pair<int, int> lever; // L 좌표
    
    for(int i = 0; i<N+2; i++){
        for(int j = 0; j<M+2; j++){
            if(map[i][j] == 'S'){
                start = {i, j};
            }
            else if(map[i][j] == 'E'){
                end = {i, j};
            }
            else if(map[i][j] == 'L'){
                lever = {i, j};
            }
        }
    }
    
    
    for(int i = 0; i<N+2; i++){
        for(int j = 0; j<M+2; j++){
            cout << map[i][j];
        }
        cout << endl;
    }
    
    
    
    // 레버로 가는 길
    vector<vector<int>> visit1(N+2, vector<int>(M+2, 0)); // 레버 찾는 길에 쓰는 방문 배열
    queue<pair<pair<int, int>, int>> q1; // 레버 찾는 길에 쓰일 큐. <<x,y>, time>
    q1.push({start, 1}); // 원랜 0인데 시작점 다시 방문 방지하려고 1로 함.
    visit1[start.first][start.second] = 1; // 원랜 0인데 시작점 다시 방문 방지하려고 1로 함. 최종 걸린 시간에서 1 빼줘야함
    while(!q1.empty()){
        pair<int, int> now = q1.front().first;
        int t = q1.front().second;
        q1.pop();
        if(now == lever){
            break;
        }
        for(int i = 0; i<4; i++){
            int go_x = now.first + dx[i];
            int go_y = now.second + dy[i];
            // (X가 아닌 곳 중에서)한 번도 안가본 곳 방문
            if(!visit1[go_x][go_y] && !(map[go_x][go_y] == 'X')){
                visit1[go_x][go_y] = t+1;
                q1.push({{go_x, go_y}, t+1});
            }
        }
    }
    // 레버까지 도달 못함
    if(!visit1[lever.first][lever.second]){
        cout << lever.first << " " << lever.second << " ";
        cout << "cant go lever!";
        return -1;
    }
    int s_to_l = visit1[lever.first][lever.second]-1; // S부터 L까지 걸리 시간
    
    // 출구로 가는길
    vector<vector<int>> visit2(N+2, vector<int>(M+2, 0)); // 출구 찾는 길에 쓰는 방문 배열
    queue<pair<pair<int, int>, int>> q2; // 출구 찾는 길에 쓰일 큐. <<x,y>, time>
    q2.push({lever, 1});
    visit2[lever.first][lever.second] = 1;
    while(!q2.empty()){
        pair<int, int> now = {q2.front().first.first, q2.front().first.second};
        int t = q2.front().second;
        q2.pop();
        if(now == end){
            break;
        }
        for(int i = 0; i<4; i++){
            int go_x = now.first + dx[i];
            int go_y = now.second + dy[i];
            if (go_x < 0 || go_x >= N + 2 || go_y < 0 || go_y >= M + 2) continue;
            // (X가 아닌 곳 중에서)한 번도 안가본 곳 방문
            if(!visit2[go_x][go_y] && !(map[go_x][go_y] == 'X')){
                visit2[go_x][go_y] = t+1;
                q2.push({{go_x, go_y}, t+1});
            }
        }
    }
    // 출구까지 도달 못함
    if(!visit2[end.first][end.second]){
        return -1;
    }
    int l_to_e = visit2[end.first][end.second]-1;
    
    answer = s_to_l + l_to_e;
    
    return answer;
}