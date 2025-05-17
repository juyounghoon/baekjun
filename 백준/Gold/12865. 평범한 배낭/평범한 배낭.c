#include <stdio.h>

#define MAX_N 100
#define MAX_W 100000

int N, K;
int DP[MAX_W+1]; // [w]: w무게일 때 최대 value
typedef struct Thing{
    int w, v;
}Thing;

int get_max(int a, int b){
    if(a>b) return a;
    else return b;
}

int main(){
    scanf("%d %d", &N, &K);
    Thing things[MAX_N];
    for(int i = 0; i<N; i++){
        scanf("%d %d", &things[i].w, &things[i].v);
    }
    for(int i = 0; i<N; i++){
        int w = things[i].w;
        int v = things[i].v;
        for(int j = K; j>=w; j--){
            DP[j] = get_max(DP[j], DP[j-w] + v);
        }
    }
    printf("%d", DP[K]);
    
    return 0;
}
/*
dp[w+things[i].w] = dp[w+things[i].w] or dp[w] + things[i].v
*/