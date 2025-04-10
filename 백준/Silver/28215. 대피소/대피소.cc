#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX_DIST 200000
int N, K;
vector<pair<int, int>> home;

int FindDistance(pair<int, int> &a, pair<int, int> &b){
    int delta_x, delta_y;
    delta_x = abs(a.first - b.first);
    delta_y = abs(a.second - b.second);
    return (delta_x + delta_y);
}

// home에서 r개의 대피소를 선택하는 함수. 인덱스를 고름
void Combination(int current, int r, vector<int> &collected, vector<vector<int>> &comb){
    if(collected.size() == r){
        comb.push_back(collected);
        return;
    }
    for(int i = current; i<home.size(); i++){
        collected.push_back(i);
        Combination(i + 1, r, collected, comb);
        collected.pop_back();
    }
}

int main(){
    cin >> N >> K;
    home.resize(N);
    for(int i = 0; i<N; i++){
        int x, y;
        cin >> x;
        cin >> y;
        home[i].first = x;
        home[i].second = y;
    }
    vector<int> collected;
    vector<vector<int>> comb;
    Combination(0, K, collected, comb);
    
    // 각 조합에 대해 거리를 모두 구하고 그 중 최대 값 구하기
    int min = MAX_DIST;
    for(int i = 0; i<comb.size(); i++){
        int max = 0; // 대피소와 가장 멀리 떨어진 집과의 거리
        for(int j = 0; j<home.size(); j++){
            int dist_to_dps = MAX_DIST; // 대피소 까지 거리(가장 가까운)
            for(int k = 0; k<comb[i].size(); k++){
                int temp = FindDistance(home[j], home[comb[i][k]]);
                if(temp < dist_to_dps){
                    dist_to_dps = temp;
                }
            }

            //대피소 까지의 거리가 원래 값보다 크면 갱신
            if(dist_to_dps > max){
                max = dist_to_dps;
            }
        }
        if(max < min){
            min = max;
        }
    }

    cout << min;

    return 0;
}