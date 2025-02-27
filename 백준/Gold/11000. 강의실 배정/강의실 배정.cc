#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N;
int room = 0;
vector<pair<int, int> > cls; // 수업 정보를 담을 배열 <시작시간, 끝시간>
priority_queue<int, vector<int>, greater<int> > pq;

bool compare(pair<int, int> a, pair<int, int> b){
    if(a.first == b.first){
        return a.second > b.second;
    }
    return a.first < b.first;
}

int main(){
    cin >> N;
    int s, e;
    for(int i = 0; i<N; i++){
        cin >> s >> e;
        cls.push_back(make_pair(s,e));
    }
    sort(cls.begin(), cls.end(), compare);

    pq.push(cls[0].second);
    room++;
    for(int i = 1; i<N; i++){
        if(pq.top() <= cls[i].first){
            pq.pop();
            pq.push(cls[i].second);
        }
        else{
            pq.push(cls[i].second);
            room++;
        }
    }
    cout << room;

    return 0;
}