#include <stdio.h>

#define MAX_N 1500000

int N;
int T[MAX_N+1];
int P[MAX_N+1];
int Pay[MAX_N+1]; // [i] = i일까지 일했을 때 받을 수 있는 최대 수익

int get_max(int a, int b){
    return a > b ? a : b;
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i<=N; i++){
        scanf("%d %d", &T[i], &P[i]);
    }

    Pay[1] = 0;
    for(int i = 1; i<=N; i++){
        if(i+T[i] <= N+1){
            Pay[i+T[i]] = get_max(Pay[i] + P[i], Pay[i+T[i]]);
        }
        if(i+1 <= N+1){
            Pay[i+1] = get_max(Pay[i], Pay[i+1]);
        }
    }
    printf("%d", Pay[N+1]);

    return 0;
}