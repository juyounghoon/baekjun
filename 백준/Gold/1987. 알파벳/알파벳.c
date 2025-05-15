#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int R, C;
char map[MAX+2][MAX+2];
bool visited[MAX+2][MAX+2] = {false};
bool AlphaSet[26] = {false};
// 0: A, 1: B, 2: C, ... , 24: Y, 25: Z

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int tot_cnt = 0;

typedef struct LocInfo{
    int r;
    int c;
    int cnt;
}LocInfo;

// char to num. 알파벳을 0~25으로 변환
int cton(char alpha){
    return (int)alpha - 65;
}

void DFS(bool visited[MAX+2][MAX+2], bool *AlphaSet, LocInfo curr, int R, int C){
    visited[curr.r][curr.c] = true;
    AlphaSet[cton(map[curr.r][curr.c])] = true;
    tot_cnt = tot_cnt < curr.cnt ? curr.cnt : tot_cnt;

    for(int i = 0; i<4; i++){
        int next_r = curr.r + dr[i];
        int next_c = curr.c + dc[i];
        if(next_r < 1 || next_r > R || next_c < 1 || next_c > C) continue;
        if(!visited[next_r][next_c] && !AlphaSet[cton(map[next_r][next_c])]){
            LocInfo next;
            next.r = next_r;
            next.c = next_c;
            next.cnt = curr.cnt + 1;
            DFS(visited, AlphaSet, next, R, C);
        }
    }
    visited[curr.r][curr.c] = false;
    AlphaSet[cton(map[curr.r][curr.c])] = false;
}

int main(){
    scanf("%d %d", &R, &C);
    for(int i = 1; i<=R; i++){
        for(int j = 1; j<=C; j++){
            scanf(" %1c", &map[i][j]);
        }
    }

    LocInfo start;
    start.c = 1;
    start.r = 1;
    start.cnt = 1;

    DFS(visited, AlphaSet, start, R, C);

    printf("%d", tot_cnt);

    return 0;
}