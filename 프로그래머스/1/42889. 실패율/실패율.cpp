#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 실패율: 도달했지만 클리어 못한 플레이어 / 도달 플레이어 수
bool cmp(int a, int b){
    return a > b;
}

bool cmp2(pair<int, double> a, pair<int, double> b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    return a.second > b.second;
}

/*
1. stages 벡터 먼저 내림차순으로 sort
2. 가장 낮은 stage 부터 순회하면서 각 stage 실패율 구하기.
    6 => N+1이므로 모두 클리어한 플레이어 => [5] 도달: 1, 클리어못함: 0
    4 => [4] 도달: 2, 클리어못함: 1
    33 => [3] 도달: 4, 클리어못함: 2
    222 => [2] 도달: 7, 클리어못함: 3
    1 => [1] 도달: 8, 클리어못함: 1
3. 
*/

// N: 전체 스테이지 수, stages: 사용자가 현재 멈춰있는 스테이지의 번호
// 실패율이 높은 스테이지부터 내림차순으로 스테이지가 담겨있는 배열을 반환하는 함수
vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<pair<int, float>> ans; // [스테이지] <스테이지, 실패율>
    ans.resize(N+1);
    for(int i = 0; i<N+1; i++){
        ans[i] = {i, 0};
    }
    sort(stages.begin(), stages.end(), cmp);
    for(int i = 1, j = 0; i < stages.size() + 1; i++, j++){
        int cnt = 1;
        while(stages[i] == stages[j]){
            cnt++;
            i++;
            j++;
        }
        if(stages[j] == N+1){
            continue;
        }
        //printf("%f ", (float)cnt/i);
        //printf("i: %d, cnt: %d \n", i, cnt);
        ans[stages[j]] = {stages[j], (float)cnt/i};
        //ans.push_back(make_pair(stages[j], (float)cnt/i));
    }
    ans.erase(ans.begin());
    sort(ans.begin(), ans.end(), cmp2);
    for(auto &k: ans){
        //cout << k.first << " " << k.second << '\n';
        answer.push_back(k.first);
    }
    
    return answer;
}