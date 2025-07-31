#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> map(N+1);
    vector<int> dist(N+1, 100000000);
    vector<bool> visited(N+1, false);
    for(int i = 0; i<M; i++){
        int s, e, c;
        cin >> s >> e >> c;
        map[s].push_back({e, c});
    }

    int start, end;
    cin >> start >> end;
    dist[start] = 0;
    for(int i = 1; i<=N; i++){
        int next = 0;
        for(int j = 1; j<=N; j++){
            if(!visited[j] && dist[j] < dist[next]) next = j;
        }
        visited[next] = true;
        for(auto &k: map[next]){
                int n = k.first;
                int cost = k.second;
                if(cost + dist[next] < dist[n]) dist[n] = cost + dist[next];
            }
    }
    cout << dist[end];

    return 0;
}