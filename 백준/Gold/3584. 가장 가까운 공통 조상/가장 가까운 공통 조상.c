#include <stdio.h>

#define MAX 10000

// 본인을 포함해서 족보 생성 by DFS
int PushParents(int node, int *ParentArray, int *Tree){
    int cnt = 0;
    if(Tree[node]){
        cnt = PushParents(Tree[node], ParentArray, Tree);
    }
    ParentArray[cnt++] = node;
    return cnt;
}

// 부모를 순차적으로 배열에 push
int solution(int N){
    int Tree[MAX+1]= {0}; // Tree[child] = {부모}
    int node_1, node_2; // 입력받을 노드1, 2
    int ParentArray_1[N]; // node_1의 족보 = {조상, ... , 조부모, 부모, 본인, ... , 0, 0};
    int ParentArray_2[N]; // node_2의 족보 = {조상, ... , 조부모, 부모, 본인, ... , 0, 0};
    
    int parent, child;
    for(int i = 0; i<N-1; i++){
        scanf("%d %d", &parent, &child);
        Tree[child] = parent;
    }
    scanf("%d %d", &node_1, &node_2);
    if(node_1 == node_2){
        return node_1;
    }

    int len1 = PushParents(node_1, ParentArray_1, Tree);
    int len2 = PushParents(node_2, ParentArray_2, Tree);
    int min_len = len1 < len2 ? len1 : len2;
    
    int ans = 0;
    while (ans < min_len && ParentArray_1[ans] == ParentArray_2[ans]) {
        ans++;
    }
    //for(;ParentArray_1[ans] == ParentArray_2[ans]; ans++);

    return ParentArray_1[ans-1];
}

int main(){
    int T;
    scanf("%d", &T);
    for(int i = 0; i<T; i++){
        int N;
        scanf("%d", &N);
        printf("%d\n", solution(N));
    }

    return 0;
}