#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

int Find(int x, vector<int> &parent){
    if(parent[x] == x){
        return x;
    }
    return parent[x] = Find(parent[x], parent);
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    vector<int> parent(n);
    for(int i = 0; i<n; i++){
        parent[i] = i;
    }
    for(int i = 0; i<computers.size(); i++){
        for(int j = 0; j<computers[0].size(); j++){
            if(computers[i][j]){
                int rooti = Find(i, parent);
                int rootj = Find(j, parent);
                if(rooti != rootj){
                    parent[rooti] = rootj;
                }
            }
        }
    }
    
    set<int> real_roots;
    for(int i = 0; i<parent.size(); i++){
        int root = Find(i, parent);
        real_roots.insert(root);
    }
    
    answer = real_roots.size();
    
    return answer;
}