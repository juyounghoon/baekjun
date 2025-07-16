#include <iostream>
#include <vector>

using namespace std;
int N, M;
int CntCCTV; // CCTV의 수
int ans;
vector<pair<pair<int, int>, int>> cctvs; // {{n, m}, type}
vector<vector<int>> office;

// 오 위 왼 아래
int dn[] = {0, -1, 0, 1};
int dm[] = {1, 0, -1, 0};

vector<vector<vector<int>>> CCTV_Dir = {
    {},
    {{0}, {1}, {2}, {3}},
    {{0, 2}, {1, 3}},
    {{0, 1}, {1, 2}, {2, 3}, {3, 0}},
    {{0, 1, 2}, {1, 2, 3}, {2, 3, 0}, {3, 0, 1}},
    {{0, 1, 2, 3}}
};

void CCTV_On(vector<vector<int>> &office, int n, int m, int dir, vector<pair<int, int>>& changed){
    while(1){
        n += dn[dir];
        m += dm[dir];
        if(n<0 || m<0 || n>=N || m>=M || office[n][m] == 6) break;
        if(office[n][m] == 0){
            office[n][m] = 7;
            changed.push_back({n, m});
        }
    }
}

void CCTV_Off(vector<vector<int>> &office, vector<pair<int, int>> changed){
    for(pair c: changed){
        int n = c.first;
        int m = c.second;
        office[n][m] = 0;
    }
}

int Count_SaGak(const vector<vector<int>> &office){
    int cnt = 0;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            if(office[i][j] == 0) cnt++;
        }
    }
    return cnt;
}

void Find(vector<vector<int>> &office, int idx){
    if(idx == CntCCTV){
        int cnt = Count_SaGak(office);
        if(cnt < ans){
            ans = cnt;
        }
        return;
    }

    int n = cctvs[idx].first.first;
    int m = cctvs[idx].first.second;
    int type = cctvs[idx].second;
    
    for(auto dir: CCTV_Dir[type]){
        vector<pair<int, int>> changed;
        for(auto d: dir){
            CCTV_On(office, n, m, d, changed); 
        }
        Find(office, idx+1);
        CCTV_Off(office, changed);
    }
}

int main(){
    cin >> N >> M;
    ans = N*M;
    office.resize(N, vector<int>(M));
    for(int i = 0; i<N; i++){
        for(int j = 0; j<M; j++){
            cin >> office[i][j];
            if(office[i][j]>=1 && office[i][j]<=5){
                cctvs.push_back({{i, j}, office[i][j]});
                CntCCTV++;
            }
        }
    }
    
    Find(office, 0);
    cout << ans;

    return 0;
}