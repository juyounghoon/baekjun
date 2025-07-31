#include <iostream>
#include <vector>
#include <queue>

#define MAX 10000000

using namespace std;

int N, M;
int v1, v2;
vector<vector<int>> final;

void Dijkstra(int start, const vector<vector<pair<int, int>>> &map){
    vector<int> dist(N+1, MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while(!pq.empty()){
        int cost_curr = pq.top().first;
        int node_curr = pq.top().second;
        pq.pop();

        if(cost_curr>dist[node_curr]) continue;

        for(auto &k: map[node_curr]){
            int next = k.first;
            int cost = k.second;
            if(dist[next] > cost_curr + cost){
                dist[next] = cost_curr + cost;
                pq.push({dist[next], next});
            }
        }
    }
    if(start == 1){
        final[1][v1] = dist[v1];
        final[v1][1] = dist[v1];

        final[1][v2] = dist[v2];
        final[v2][1] = dist[v2];
    }
    else if(start == v1){
        final[v1][v2] = dist[v2];
        final[v2][v1] = dist[v2];

        final[v1][N] = dist[N];
        final[N][v1] = dist[N];
    }
    else if(start == v2){
        final[v2][N] = dist[N];
        final[N][v2] = dist[N];
    }
}

int main(){
    int ans = -1;
    cin >> N >> M;

    vector<vector<pair<int, int>>> map(N+1);
    final = vector<vector<int>>(N+1, vector<int>(N+1, MAX));
    for(int i = 0; i<M; i++){
        int s, e, c;
        cin >> s >> e >> c;
        map[s].push_back({e, c});
        map[e].push_back({s, c});
    }

    cin >> v1 >> v2;

    Dijkstra(1, map);
    Dijkstra(v1, map);
    Dijkstra(v2, map);

    int best_route = min(final[1][v1]+final[v1][v2]+final[v2][N], final[1][v2]+final[v2][v1]+final[v1][N]);
    if(best_route < MAX) ans = best_route;

    cout << ans;

    return 0;
}