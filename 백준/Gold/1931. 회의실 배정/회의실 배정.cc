#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
vector<pair<int, int> > t; // <시작시간, 끝시간>
int ans;

bool compare(const pair<int, int> &a, const pair<int, int> &b);

int main(){
    cin >> N;
    int start, end;
    for(int i = 0; i<N; i++){
        cin >> start >> end;
        t.emplace_back(start, end);
    }
    if(N == 1){
        cout << 1;
        return 0;
    }
    // 끝나는 시간이 빠른순으로, 끝나는 시간이 같으면 시작시간이 빠른순으로 정렬
    sort(t.begin(), t.end(), compare);

    int current = 0;
    ans = 1;
    for(int i = 1; i<N; i++){
        if(t[i].first >= t[current].second){
            current = i;
            ans++;
        }
    }

    cout << ans;
    return 0;
}

bool compare(const pair<int, int> &a, const pair<int, int> &b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    return a.second < b.second;
}