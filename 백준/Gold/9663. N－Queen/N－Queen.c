#include <stdio.h>
#include <stdlib.h>

int N;

int* m1; // 왼쪽만 체크
int* m2; // 왼쪽 아래 대각선 방향 체크
int* m3; // 왼쪽 위 대각선 방향 체크

// 끝까지 도달한 횟수
int cnt = 0;

// N을 입력받아서 map을 초기화
void Init();

// 0~N-1 보면서 놓을 수 있는지 확인
// i에 놓을 수 있으면 놓고 -> 재귀
// 놓을 수 없으면 다음(i+1)
// 종료조건: 끝 행(N-1) 도달
void Queen(int m);

// 방문이력(m1, m2, m3) 체크해서 놓을 수 있는지 확인. 놓을 수 있으면 1, 없으면 0반환
int Check(int i, int m);

// 놓을 수 있는 경우 실행하는 함수. [i][m]에 퀸을 놓아서 방문이력 체크. x에 1넣으면 퀸을 놓음, 0을 놓으면 퀸을 다시 뺌.
void QueenOnMap(int i, int m, int x);

int main(){
    Init();
    Queen(0);

    printf("%d", cnt);

    free(m1);
    free(m2);
    free(m3);

    return 0;
}

void Init(){
    (void)scanf("%d", &N);

    m1 = (int*)calloc(N, sizeof(int));
    m2 = (int*)calloc(2 * N - 1, sizeof(int));
    m3 = (int*)calloc(2 * N - 1, sizeof(int));
}

void Queen(int m){
    // 0행부터 N-1행까지 순회하면서 체크
    for(int i = 0; i < N; i++){
        //놓을 수 있는지 판단.
        if(Check(i, m)){
            if(m == N -1){ // 종료 조건
                cnt++;
                return;
            }
            QueenOnMap(i, m, 1);
            Queen(m+1);
            QueenOnMap(i, m, 0);
        }
    }
    return;
}

int Check(int i, int m){
    return m1[i] == 0 && m2[i + m] == 0 && m3[i - m + N - 1] == 0;
}

void QueenOnMap(int i, int m, int x){
    m1[i] = x;
    m2[i+m] = x;
    m3[i - m + N - 1] = x;
}