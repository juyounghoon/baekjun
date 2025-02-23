#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <tuple>

using namespace std;

int N, M;

// N+1 by M+2 크기의 벽 생성. 벽 둘래를 -1로 둘러쌈. 0: 길. 1: 벽, -1: 맵 밖
vector<vector<int> > map;
// visited 배열의 모든 요소는 -1로 초기화
vector<vector<int> > visited; // 방문한 곳까지 거리
vector<vector<int> > visited_broken; // 방문한 곳까지 거리
//deque<tuple<int, int, int> > q; // n, m, brk(벽을 부쉈는지 여부)
deque<pair<pair<int, int>,int> > q;

int dn[] = {0, 1, 0, -1};
int dm[] = {1, 0, -1, 0};

void Find();

int main(){
    int ans;
    cin >> N >> M;

    string input;
    map.resize(N+2, vector<int>(M+2, -1));
    visited.resize(N+2, vector<int>(M+2,-1));
    visited_broken.resize(N+2, vector<int>(M+2,-1));
    for(int i = 1; i<N+1; i++){
        cin >> input;
        for(int j = 1; j<M+1; j++){
            map[i][j] = input[j-1] - '0';
        }
    }


    // 1,1에서 출발, 벽 부술 수 있음.
    q.push_back(make_pair(make_pair(1,1), 1));
    visited[1][1] = 1;
    visited_broken[1][1] = 1;
    while(!q.empty()){
        Find();
    }

    if(visited[N][M] == -1 && visited_broken[N][M] == -1){
        ans = -1;
    }
    else if(visited[N][M] == -1){
        ans = visited_broken[N][M];
    }
    else if(visited_broken[N][M] == -1){
        ans = visited[N][M];
    }
    else if(visited[N][M] < visited_broken[N][M]){
        ans = visited[N][M];
    }
    else{
        ans = visited_broken[N][M];
    }
    cout << ans;

    return 0;
}

void Find(){
    // 벽을 깬적이 없는 경로
    if(q.front().second == 1){
        for(int i = 0; i<4; i++){
            int n = q.front().first.first + dn[i];
            int m = q.front().first.second + dm[i];
            // 정상적인 길로 가는 경우
            if(map[n][m] == 0){
                if(visited[n][m] == -1 || visited[n][m] > visited[q.front().first.first][q.front().first.second] + 1){
                    visited[n][m] = visited[q.front().first.first][q.front().first.second] + 1;
                    q.push_back(make_pair(make_pair(n,m), q.front().second));
                }
            }
            // 벽을 깨고 이동하는 경우
            // 벽을 깬 후 다시 4방향 확인
            else if(map[n][m] == 1){
                for(int j = 0; j<4; j++){
                    int n_new = n + dn[j];
                    int m_new = m + dm[j];
                    if(dn[i] == -dn[j] && dm[i] == -dm[j]){
                        continue;
                    }
                    if(map[n_new][m_new] == 0){
                        if(visited_broken[n_new][m_new] == -1 || visited_broken[n_new][m_new] > visited[q.front().first.first][q.front().first.second] + 2){
                            visited_broken[n_new][m_new] = visited[q.front().first.first][q.front().first.second] + 2;
                            q.push_back(make_pair(make_pair(n_new,m_new),0));
                        }
                    }
                }
            }
        }
        q.pop_front();
    }
    // 이미 벽을 한 번 깬 적이 있는 경로
    else if(q.front().second == 0){
        for(int i = 0; i<4; i++){
            int n = q.front().first.first + dn[i];
            int m = q.front().first.second + dm[i];
            if(map[n][m] == 0){
                if(visited_broken[n][m] == -1 || visited_broken[n][m] > visited_broken[q.front().first.first][q.front().first.second] + 1){
                    // v_b에 방문 이력 저장
                    visited_broken[n][m] = visited_broken[q.front().first.first][q.front().first.second] + 1;
                    q.push_back(make_pair(make_pair(n,m), q.front().second));

                }
            }
        }
        q.pop_front();
    }
}