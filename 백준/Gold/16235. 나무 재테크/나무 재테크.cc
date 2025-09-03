#include <iostream>
#include <vector>

using namespace std;

// 위 위오 오 아래오 아래 아래왼 왼 위왼
int dn[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dm[] = {0, 1, 1, 1, 0, -1, -1, -1};

int N, M, K; // N: 땅의 크기, M: 나무의 수, K: K년 후
vector<vector<int>> A; // 양분 map
vector<vector<int>> A_Plus;
vector<vector<vector<int>>> trees; // 나무 map [n][m] = (나무1 나이, 나무2 나이, ...}

void Spring_Summer();
void Fall();
void Winter();

int CountTrees(){
    int cnt = 0;
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            cnt += trees[i][j].size();
        }
    }
    return cnt;
}

// 봄: 나무가 나이만큼 양분 먹고 나이++(어린 나무먼저), 양분이 부족해 먹지 못하면 즉사
// 여름: 죽은 나무가 양분으로 변함. 양분 += 죽은 나무 나이 / 2
void Spring_Summer(){
    //vector<vector<int>> dead;
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            vector<int> survived;
            int dead_food = 0;
            for(int k = 0; k<trees[i][j].size(); k++){
                if(A[i][j] >= trees[i][j][k]){
                    A[i][j] -= trees[i][j][k];
                    survived.push_back(trees[i][j][k]+1);
                }
                else{
                    dead_food += trees[i][j][k]/2;
                }
            }
            trees[i][j].swap(survived);
            A[i][j] += dead_food;
        }
    }
}



// 가을: 나이가 5의 배수인 나무 번식. 인접8칸에 나이가 1인 나무 생김
void Fall(){
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            for(int k = 0; k<trees[i][j].size(); k++){
                if(trees[i][j][k]%5 != 0) continue;
                for(int l = 0; l<8; l++){
                    int next_n = i+dn[l];
                    int next_m = j+dm[l];
                    if(next_n<1 || next_m<1 || next_n>N || next_m>N) continue;
                    trees[next_n][next_m].insert(trees[next_n][next_m].begin(), 1);
                }
            }
        }
    }
}

// 겨울: 갹 칸에 양분 추가
void Winter(){
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            A[i][j] += A_Plus[i][j];
        }
    }

}

int main(){
    cin >> N >> M >> K;
    A = vector<vector<int>>(N+2, vector<int>(N+2, 5));
    A_Plus = vector<vector<int>>(N+2, vector<int>(N+2));
    trees = vector<vector<vector<int>>>(N+2, vector<vector<int>>(N+2));
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> A_Plus[i][j];
        }
    }

    for(int i=0; i<M; i++){
        int x, y, z; cin >> x >> y >> z;
        trees[x][y].push_back(z);
    }

    for(int i = 0; i<K; i++){
        Spring_Summer();
        Fall();
        Winter();
    }

    cout << CountTrees();

    return 0;
}
/*
봄: 나무가 나이만큼 양분 먹고 나이++
    양분이 부족해 먹지 못하면 즉사
여름: 죽은 나무가 양분으로 변함. 양분 += 죽은 나무 나이 / 2
가을: 나이가 5의 배수인 나무 번식. 인접8칸에 나무 생김
겨울: 갹 칸에 양분 추가
*/