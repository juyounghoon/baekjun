#include <iostream>
#include <vector>

using namespace std;

typedef struct Shark{
    int r, c; // 위치
    int s; // 속력
    int d; // 방향(1: 위, 2: 아래, 3: 오른, 4: 왼)
    int z; // 크기
    bool live; // 살아있는 상어인지 죽은 상어인지
} Shark;

// 0: 깍뚜기, 1: 위, 2: 아래, 3: 오른, 4: 왼
vector<vector<int>> dir = {{0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1}};

int R, C, M;
vector<vector<int>> map; // -1: 상어 없음, 0이상: 해당 좌표에 위치한 상어의 인덱스 변호
vector<Shark> sharks;

int ans;
int ReverseDir(int d);

int ReverseDir(int d){
    if(d == 1 || d == 3) return d+1;
    else if(d == 2 || d == 4) return d-1;
    else return 0;
}

void FishHook(int fisher){ // 낚시행위
    for(int i = 1; i<=R; i++){
        if(map[i][fisher] != -1){
            int shark = map[i][fisher];
            ans += sharks[shark].z;
            sharks[shark].live = false;
            map[i][fisher] = -1;
            break;
        }
    }
}

void SharkMove(){ // 상어 이동 후 같은 위치면 큰 상어가 잡아먹음
    vector<vector<vector<int>>> multisharks(R+1, vector<vector<int>>(C+1)); // 한 좌표에 여러마리의 상어 배열. [r][c] = {상어 인덱스, 상어 인덱스, ...}
    
    // 모든 상어 이동
    for(int i = 0; i<sharks.size(); i++){
        if(!sharks[i].live) continue;

        int curr_r = sharks[i].r;
        int curr_c = sharks[i].c;
        int curr_d = sharks[i].d;

        map[curr_r][curr_c] = -1;

        // 이동 후 상어의 위치, 방향
        int new_r = curr_r + dir[curr_d][0]*sharks[i].s;
        int new_c = curr_c + dir[curr_d][1]*sharks[i].s;
        int new_d = curr_d;
        
        if(curr_d == 1 || curr_d == 2){
            // 방향 갱신
            if(new_r>=1 && new_r<=R) new_d = new_d;
            else if(new_r>R && ((new_r-1)/(R-1))%2 == 1) new_d = ReverseDir(new_d);
            else if(new_r>R && ((new_r-1)/(R-1))%2 == 0) new_d = new_d;
            else if(new_r<=0 && (new_r/(R-1))%2 == 0) new_d = ReverseDir(new_d);
            else if(new_r<=0 && (new_r/(R-1))%2 == -1) new_d = new_d;

            // 위치 갱신
            new_r %= (2*R-2);
            if(new_r<0) new_r += (2*R-2);
            if(new_r == 0) new_r = 2;
            if(new_r>R) new_r = R-(new_r-R);
        }
        else if(curr_d == 3 || curr_d == 4){
            // 방향 갱신
            if(new_c>=1 && new_c<=C) new_d = new_d;
            else if(new_c>C && ((new_c-1)/(C-1))%2 == 1) new_d = ReverseDir(new_d);
            else if(new_c>C && ((new_c-1)/(C-1))%2 == 0) new_d = new_d;
            else if(new_c<=0 && (new_c/(C-1))%2 == 0) new_d = ReverseDir(new_d);
            else if(new_c<=0 && (new_c/(C-1))%2 == -1) new_d = new_d;

            // 위치 갱신
            new_c %= (2*C-2);
            if(new_c<0) new_c += (2*C-2);
            if(new_c == 0) new_c = 2;
            if(new_c>C) new_c = C-(new_c-C);
        }

        sharks[i].r = new_r;
        sharks[i].c = new_c;
        sharks[i].d = new_d;
        multisharks[new_r][new_c].push_back(i);
    }

    // 이동 후 상어 그대로 있거나, 잡아먹거나, 잡아먹히거나
    for(int i = 1; i<=R; i++){
        for(int j = 1; j<=C; j++){
            for(int k = 0; k<multisharks[i][j].size(); k++){
                int curr_shark = map[i][j];
                int new_shark = multisharks[i][j][k];
                if(curr_shark == -1) map[i][j] = new_shark; // 빈집 털이
                else if(!sharks[curr_shark].live) map[i][j] = new_shark;
                else{
                    if(sharks[curr_shark].z < sharks[new_shark].z){ // 잡아먹음
                        map[i][j] = new_shark;
                        sharks[curr_shark].live = false;
                    }
                    else{ // 잡아먹힘
                        sharks[new_shark].live = false;
                    }
                }
            }
        }
    }
}

int main(){
    cin >> R >> C >> M;
    map = vector<vector<int>>(R+1, vector<int>(C+1, -1));
    ans = 0;
    for(int i = 0; i<M; i++){
        int r, c, s, d, z;
        cin >> r >> c >> s >> d >> z;
        Shark shark = {r, c, s, d, z, true};
        sharks.push_back(shark);
        map[r][c] = i;
    }

    for(int fisher = 1; fisher<=C; fisher++){
        FishHook(fisher);
        SharkMove();
    }
    cout << ans << "\n";

    return 0;
}