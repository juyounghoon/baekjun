#include <stdio.h>
#include <string.h>

#define MAX_N 101
#define MAX_W 100001

typedef struct Thing{
    int w;
    int v;
}Thing;

Thing things[MAX_N];
int BackPack[MAX_N][MAX_W] = {-1};

int BP(int n, int w){
    if(n<0 || w<0) return 0;
    if(BackPack[n][w] == -1){
        int include, except;
        if(n-1<0 ||  w-things[n].w < 0) include = 0;
        else include = BP(n-1, w-things[n].w) + things[n].v;

        if(n-1<0) except = 0;
        else except = BP(n-1, w);

        BackPack[n][w] = include < except ? except : include;
    }
    return BackPack[n][w];
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);

    for(int i = 1; i<=N; i++){
        int tmp_w, tmp_v;
        scanf("%d %d", &tmp_w, &tmp_v);
        things[i].w = tmp_w;
        things[i].v = tmp_v;
    }

    memset(BackPack, -1, sizeof(BackPack));
    for(int i = 0; i<=K; i++){
        BackPack[0][i] = 0;
    }

    printf("%d", BP(N, K));

    return 0;
}
/*
BP(n,w) = max(BP(n-1, w-things[i].w) + things[i].v, BP(n-1, w))
*/