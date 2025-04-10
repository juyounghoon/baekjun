#include <iostream>
#include <vector>
using namespace std;

#define MAX 500000
vector<vector<pair<int, int>>> village; // [출발] = {<도착, 비용>, <도착, 비용>, ...}
vector<int> dist; // 1번도시와 각 도시와의 거리
vector<bool> visit; // 방문 이력

void Find(int current, vector<vector<pair<int, int>>> &village){   
    for(int i = 0; i<village[current].size(); i++){
        int arrive = village[current][i].first;
        int cost = village[current][i].second;
        if(dist[current] + cost <= dist[arrive]){
            dist[arrive] = dist[current] + cost;
            Find(arrive, village);
        }
    }
}

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;
    
    dist.resize(N+1, MAX); // 각 도시와 1번도시와의 거리
    dist[1] = 0;

    village.resize(N+1);
    visit.resize(N+1);
    
    for(const auto &r: road){
        int start1 = r[0];
        pair end_cost1 = {r[1], r[2]};
        
        int start2 = r[1];
        pair end_cost2 = {r[0], r[2]};
        
        village[start1].push_back(end_cost1);
        village[start2].push_back(end_cost2);
        
        if(r[0] == 1){
            dist[r[1]] = r[2];
        }
        else if(r[1] == 1){
            dist[r[0]] = r[2];
        }
    }
    Find(1, village);
    
    for(int i = 1; i<dist.size(); i++){
        if(dist[i] <= K){
            answer++;
        }
    }    

    return answer;
}