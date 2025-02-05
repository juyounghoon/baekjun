#include <stdio.h>
#include <stdlib.h>

#define MAX 250000

int N; // 세로 크기
int M; // 가로 크기
int** map;

typedef struct Queue{
    int n;
    int m;
} Queue;

int front = 0;
int rear = 1;
int picture_cnt = 0; // 그림의 수
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

int FindPicture(Queue* que, int a, int b); // 그림 모두 찾아서 그림 크기 반환

int main(){
    int maxpicture = 0;
    // N, M, map 입력받아서 할당하기
    (void)scanf("%d", &N);
    (void)scanf("%d", &M);
    map = (int**)calloc(N + 2, sizeof(int*));
    for(int i = 0; i < N + 2;i++){
        map[i] = (int*)calloc(M + 2, sizeof(int));
    }

    for(int i = 1; i < N + 1; i++){
        for(int j = 1; j < M + 1; j++){
            (void)scanf("%d", &map[i][j]);
        }
    }

    for(int i = 1; i < N + 1; i++){
        for(int j = 1; j < M + 1; j++){
            // if map == 1 이면 시작점으로 해서 그림 크기 찾기
            if(map[i][j]){
                Queue que[MAX];
                picture_cnt++;
                front = 0;
                rear = 1;
                map[i][j] = 0;
                int thispicture = FindPicture(que, i, j);

                if(thispicture > maxpicture){
                    maxpicture = thispicture;
                }
            }
        }
    }

    printf("%d\n%d",picture_cnt, maxpicture);
    return 0;
}

int FindPicture(Queue* que, int a, int b){
    // 시작점(시작 큐)
    que[front].n = a;
    que[front].m = b;

    while(front != rear){
        for(int i = 0; i < 4; i++){
            int y = que[front].n + dy[i];
            int x = que[front].m + dx[i];
            if(map[y][x]){
                que[rear].n = y;
                que[rear].m = x;

                map[y][x] = 0; // 방문 이력 표시
                rear++;
            }
        }
        front++;
    }

    //최종 그림의 크기 반환
    return rear;
}