#include <stdio.h>

#define MAX 1000

int N; // 집의 수
int Cost[MAX][3]; //n번 집의 [n][0] = R 비용, [n][1] = G 비용, [n][2] = B 비용
int MinComb[MAX][3] = {0}; // [n][i] = n단계에서 i색을 칠했을 때 최소 비용 기억

// n단계에서 i색을 칠했을 때 최소 비용
int Sum(int n, int i){
    if(n == 0){
        MinComb[n][i] = Cost[n][i];
        return Cost[n][i];
    }
    if(MinComb[n][i]) return MinComb[n][i];
    int min = MAX*MAX;
    for(int j = 0; j<3; j++){
        if(i == j) continue;
        int sum = Cost[n][i] + Sum(n-1, j);
        min = min > sum ? sum : min;
    }
    MinComb[n][i] = min;
    return min;
}

int main(){
    int min_cost = MAX*MAX;
    scanf("%d", &N);
    for(int i = 0; i<N; i++){
        for(int j = 0; j<3; j++){
            scanf("%d", &Cost[i][j]);
        }
    }

    for(int i = 0; i<3; i++){
        int tmp_cost = Sum(N-1, i);
        min_cost = min_cost > tmp_cost ? tmp_cost : min_cost;
    }

    printf("%d\n", min_cost);

    return 0;
}