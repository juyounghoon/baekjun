#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 5000

int N, M, K;
int ans = MAX;

// r, c, s => [r][c] 중심으로 2s+1크기의 정사각형을 시계방향으로 한 바퀴 돌림

void Rotate(vector<vector<int> > &map, const int &r, const int &c, const int &s){
    for(int i = 1; i<=s; i++){
        int tmp_nw = map[r-i][c-r];
        int tmp_ne = map[r-i][c+i];
        int tmp_se = map[r+i][c+i];
        int tmp_sw = map[r+i][c-i];
        for(int j = 0; j<2*i; j++){
            map[r-i][c+i-j] = map[r-i][c+i-(j+1)];
        }
        for(int j = 0; j<2*i-1; j++){
            map[r+i-j][c+i] = map[r+i-(j+1)][c+i];
        }
        map[r-i+1][c+i] = tmp_ne;
        for(int j = 0; j<2*i-1;j++){
            map[r+i][c-i+j] = map[r+i][c-i+(j+1)];
        }
        map[r+i][c+i-1] = tmp_se;
        for(int j = 0; j<2*i-1; j++){
            map[r-i+j][c-i] = map[r-i+(j+1)][c-i];
        }
        map[r+i-1][c-i] = tmp_sw;
    }
}

vector<vector<int> > Get_Sequence(int K){
    vector<int> sequence(K);
    vector<vector<int>> result;
    for(int i = 0; i<K; i++){
        sequence[i] = i;
    }
    do {
        result.push_back(sequence);
    } while (next_permutation(sequence.begin(), sequence.end()));

    return result;
}

void Get_Min(const vector<vector<int> > &map, int N, int M){
    for(int n = 1; n<=N; n++){
        int sum = 0;
        for(int m = 1; m<=M; m++){
            sum += map[n][m];
        }
        ans = sum < ans ? sum : ans;
    }
}

int main(){
    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int> > map(N+1, vector<int>(M+1));
    vector<vector<int> > op(K, vector<int>{3});

    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=M; j++){
            cin >> map[i][j];
        }
    }

    for(int i = 0; i<K; i++){
        cin >> op[i][0] >> op[i][1] >> op[i][2];
    }
    vector<vector<int> > op_seqeunce = Get_Sequence(K);

    for(const auto &sequence: op_seqeunce){
        vector<vector<int>> temp_map = map;
        for(int i = 0; i<K; i++){;
            int idx = sequence[i];
            Rotate(temp_map, op[idx][0], op[idx][1], op[idx][2]);
        }
        Get_Min(temp_map, N, M);
    }

    cout << ans;

    return 0;
}