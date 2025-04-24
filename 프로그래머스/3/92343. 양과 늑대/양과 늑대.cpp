#include <iostream>
#include <string>
#include <vector>

using namespace std;

int max_sheep = 1;

vector<vector<int>> graph; // [부모] = {자식1, 자식2}
void DFS(int sheep, int wolf, vector<int> nodes, vector<int> &info);
void DFS(int sheep, int wolf, vector<int> nodes, vector<int> &info){
    for(int i = nodes.size()-1; i >= 0; i--){
        int next = nodes[i];
        vector<int> new_nodes;
        new_nodes.assign(nodes.begin(), nodes.end());

        if(info[next] == 0){
            new_nodes.erase(new_nodes.begin() + i);
            for(const auto &more: graph[next]){
                new_nodes.push_back(more);
            }
            if(sheep + 1 > max_sheep){
                max_sheep = sheep+1;
            }
            
            DFS(sheep+1, wolf, new_nodes, info);
        }
        else if(info[next] == 1 && sheep > wolf + 1){
            new_nodes.erase(new_nodes.begin() + i);
            for(const auto &more: graph[next]){
                new_nodes.push_back(more);
            }
            DFS(sheep, wolf+1, new_nodes, info);
        }
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    graph.resize(info.size());
    for(const auto &edge: edges){
        int parent = edge[0];
        int child = edge[1];
        graph[parent].push_back(child);
    }
    
    DFS(1, 0, graph[0], info);
    
    return max_sheep;
}