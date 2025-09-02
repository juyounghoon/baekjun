#include <iostream>
#include <vector>

#define MAX 10000000
using namespace std;

int ans;

int N, M;
vector<vector<int>> map;
vector<pair<int, int>> stores;
vector<pair<int, int>> homes;

int CalcDist(pair<int, int> a, pair<int, int> b){
    int d = 0;
    if(a.first > b.first) d += a.first - b.first;
    else d += b.first - a.first;

    if(a.second > b.second) d+= a.second - b.second;
    else d += b.second - a.second;

    return d;
}

int ShortestStore(vector<pair<int, int>> homes, vector<int> store_list){
    int distance = 0;
    for(pair<int, int> home: homes){
        int dist = MAX;
        for(int store: store_list){
            int d = CalcDist(home, stores[store]);
            if(d < dist) dist = d;
        }
        distance += dist;
    }
    return distance;
}

void DFS(int idx, int cnt, vector<int> &store_list){
    if(cnt == M){
        int chicken_dist = ShortestStore(homes, store_list);
        if(chicken_dist < ans){
            ans = chicken_dist;
        }
        return;
    }
    for(int i = idx; i<stores.size(); i++){
        store_list.push_back(i);
        DFS(i+1, cnt+1, store_list);
        store_list.pop_back();
    }
}

int main(){
    cin >> N >> M;
    ans = MAX;
    map = vector<vector<int>>(N, vector<int>(N));

    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            cin >> map[i][j];
            if(map[i][j] == 2){
                stores.push_back({i, j});
            }
            else if(map[i][j] == 1){
                homes.push_back({i, j});
            }
        }
    }
    
    vector<int> store_list;
    DFS(0, 0, store_list);
    cout << ans;

    return 0;
}