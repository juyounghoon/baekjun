#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int V, E;
vector<int> parent;

void PrintGraph(const vector<vector<int>> &graph){
    cout << "\n=====Print Graph=====\n";
    for(vector<int> g: graph){
        cout << g[0] << " -> " << g[1] << " [" << g[2] << "]\n";
    }
}

int FindRoot(int x){
    if(x == parent[x]) return x;
    else return parent[x] = FindRoot(parent[x]);
}

void UnionFind(int a, int b){
    int a_root = FindRoot(a);
    int b_root = FindRoot(b);

    if(a_root != b_root) parent[b_root] = a_root; 
}

bool Compare(const vector<int> &a, const vector<int> &b){
    return a[2] < b[2];
}

bool isCycle(int a, int b){
    if(FindRoot(a) == FindRoot(b)) return true;
    else return false;
}

int main(){
    int ans = 0;
    cin >> V >> E;
    vector<vector<int>> graph;
    parent = vector<int>(V+1);
    
    for(int i = 0; i<E; i++){
        vector<int> input(3); // {start, end, cost}
        cin >> input[0] >> input[1] >> input[2];
        graph.push_back(input);
    }

    for(int i = 1; i<=V; i++){
        parent[i] = i;
    }
    sort(graph.begin(), graph.end(), Compare);

    int cnt = 0; // 스패닝 트리에 추가된 간선 수
    for(vector<int> g: graph){
        int start = g[0];
        int end = g[1];
        int cost = g[2];

        // 사이클을 형성하면 pass
        if(isCycle(start, end)) continue;
        
        // 해당 간선을 트리에 추가
        UnionFind(start, end);
        ans += cost;
        cnt++;

        if(cnt >= V-1) break;
    }
    cout << ans << "\n";

    return 0;
}