#include <string>
#include <vector>
#include <queue>

using namespace std;

#define MAX 10000000

typedef struct info{
    int n, m;
    int dir;
    int cost;
    /*
      1
    2   0
      3
    */
}info;

int dn[] = {0, -1, 0, 1};
int dm[] = {1, 0, -1, 0};
// 0: 오른, 1: 위, 2: 왼, 3: 아래

int solution(vector<vector<int>> board) {
    int answer = 0;
    int N = board.size();
    vector<vector<vector<int>>> visit;
    visit.resize(N, vector<vector<int>>(N, vector<int>(4, MAX)));
    
    info start;
    start.n = 0, start.m = 0;
    start.dir = -1;
    start.cost = 0;
    for(int i = 0; i<4; i++){
        visit[0][0][i] = 0;
    }
    queue<info> q;
    q.push(start);
    while(!q.empty()){
        info curr = q.front();
        q.pop();
        for(int i = 0; i<4; i++){
            info next;
            next.n = curr.n + dn[i];
            next.m = curr.m + dm[i];
            if(next.n<0 || next.m<0 || next.n>=N || next.m>=N) continue;
            if(board[next.n][next.m]) continue;
            
            int add_cost = 100;
            if(curr.dir >= 0 && curr.dir != i) add_cost += 500;
            if(visit[next.n][next.m][i] > curr.cost + add_cost){
                visit[next.n][next.m][i] = curr.cost + add_cost;
                next.dir = i;
                next.cost = curr.cost + add_cost;
                q.push(next);
            }
        }
    }
    int ret = MAX;
    for(int i = 0; i<4; i++){
        ret = ret > visit[N-1][N-1][i] ? visit[N-1][N-1][i] : ret;
    }
    
    return ret;
}