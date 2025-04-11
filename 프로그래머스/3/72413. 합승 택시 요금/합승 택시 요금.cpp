#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

#define MAX 10000000

void Dji(int a, vector<int> &dist, vector<vector<pair<int, int>>> &graph){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({a, 0});
    while(!pq.empty()){
        int now = pq.top().first;
        int cost = pq.top().second;
        pq.pop();
        for(const auto &g: graph[now]){
            int next = g.first;
            int weight = g.second;
            if(cost + weight < dist[next]){
                pq.push({next, weight+cost});
                dist[next] = cost + weight;
            }
        }
    }
}

// n: 지점갯수, s: 시작지점, a: A의 도착지점, b: B의 도착지점
int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = MAX * 3;
    vector<vector<pair<int, int>>> graph(n+1); // [출발] = {<도착, 비용>, <도착, 비용>, ...}

    vector<int> dist_a(n+1, MAX);
    vector<int> dist_b(n+1, MAX);
    vector<int> dist_s(n+1, MAX);
    
    dist_a[a] = 0;
    dist_b[b] = 0;
    dist_s[s] = 0;
    
    for(const auto &f: fares){
        
        graph[f[0]].push_back({f[1], f[2]});
        graph[f[1]].push_back({f[0], f[2]});
    }
    
    Dji(s, dist_s, graph);
    Dji(a, dist_a, graph);
    Dji(b, dist_b, graph);
    
    vector<int> point(n+1, MAX*3);
    
    for(int i = 1; i<point.size(); i++){
        point[i] = dist_a[i] + dist_b[i] + dist_s[i];
        cout << point[i] << " ";
        if(point[i] < answer){
            answer = point[i];
        }
    }
    
    return answer;
}