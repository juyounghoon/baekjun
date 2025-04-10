#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> parent; // 각 노드의 부모가 누군지 담는 배열

bool cmp(vector<int> a, vector<int> b){
    return a[2] < b[2];
}

// x의 시조가 누군지 확인
/*
int FindRoot(int x){
    while(parent[x] != x){
        x = parent[x];
    }
    return x;
}
*/
int FindRoot(int x){
    if(parent[x] != x){
        parent[x] = FindRoot(parent[x]);
    }
    return parent[x];
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    int line = 0;
    parent.resize(n);
    for(int i = 0; i<n; i++){
        parent[i] = i;
    }
    sort(costs.begin(), costs.end(), cmp);

    for(int i = 0; i<costs.size(); i++){
        int node1 = costs[i][0];
        int node2 = costs[i][1];
        int cst = costs[i][2];
        
        int root1 = FindRoot(node1);
        int root2 = FindRoot(node2);
        cout << root1 << " "<< root2 << endl;
        if(root1 != root2){
            parent[root2] = root1;
            answer += cst;
            line++;
        }
        if(line == n-1){
            break;
        }
    }    
    
    return answer;
}