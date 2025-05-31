#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> map(9, vector<int>(9));
vector<vector<bool>> Check_Col(9, vector<bool>(10, true)); // [c][n]: c열에 n이 들어갈 수 있는지
vector<vector<bool>> Check_Row(9, vector<bool>(10, true)); // [r][n]: c행에 n이 들어갈 수 있는지
vector<vector<bool>> Check_Rec(9, vector<bool>(10, true)); // [r][n]: r번째 사각형 구역에 n이 들어갈 수 있는지

bool isfound = false;

void PrintMap(const vector<vector<int>> &m){
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            cout << m[i][j];
        }
        cout << "\n";
    }
}

void DFS(vector<vector<int>> &map, int curr){
    if(isfound) return;

    if(curr == 81){
        PrintMap(map);
        isfound = true;
        return;
    }

    int r = curr/9;
    int c = curr%9;
    int s = (r/3)*3 + c/3;

    if(map[r][c] > 0){
        DFS(map, curr+1);
        return;
    }

    for(int num = 1; num<=9; num++){
        if(Check_Col[c][num] && Check_Row[r][num] && Check_Rec[s][num]){
            map[r][c] = num;
            Check_Col[c][num] = false;
            Check_Row[r][num] = false;
            Check_Rec[s][num] = false;
            DFS(map, curr+1);
            map[r][c] = 0;
            Check_Col[c][num] = true;
            Check_Row[r][num] = true;
            Check_Rec[s][num] = true;
        }
    }
}

int main(){
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            scanf("%1d", &map[i][j]);
            if(map[i][j] > 0){
                int section = i/3*3 + j/3;
                Check_Col[j][map[i][j]] = false;
                Check_Row[i][map[i][j]] = false;
                Check_Rec[section][map[i][j]] = false;
            }
        }
    }
    DFS(map, 0);

    return 0;
}