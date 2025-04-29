#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> answer(1, -1);
int minimal = 0; // 가장 큰 점수 차로 승리한 경우, 가장 낮은 점수
int min_arrow = 0; // 그 가장 낮은 점수에 맞힌 화살 수
int max_diff = -1; // 가장 큰 점수 차이

void DFS(int arrow, int idx, vector<int> Ryan, vector<int> &info);
int CalcDiff(vector<int> &Ryan, vector<int> &info); // 점수 차이 계산

void DFS(int arrow, int idx, vector<int> Ryan, vector<int> &info){
    if(arrow == 0 || idx == 10){
        if(idx == 10){
            Ryan[idx] = arrow;
        }
        int s_diff = CalcDiff(Ryan, info);
        
        if(max_diff < s_diff){
            max_diff = s_diff;
            
            int min_idx = 10;
            int min_idx_arrow = 0;
            for(int i = 0; i<=10; i++){
                if(Ryan[i] > 0){
                    min_idx = i;
                    min_arrow = Ryan[min_idx];
                }
            }
            minimal = min_idx;
            min_arrow = min_idx_arrow;
            
            answer.assign(Ryan.begin(), Ryan.end());
        }
        else if(max_diff == s_diff && s_diff > 0){
            int min_idx = 10;
            int min_idx_arrow = 0;
            for(int i = 0; i<=10; i++){
                if(Ryan[i] > 0){
                    min_idx = i;
                    min_idx_arrow = Ryan[min_idx];
                }
            }
            if(min_idx > minimal){
                minimal = min_idx;
                min_arrow = Ryan[minimal];
 
                answer.assign(Ryan.begin(), Ryan.end());
            }
            else if(min_idx == minimal && min_idx_arrow > min_arrow){
                min_arrow = Ryan[minimal];
                answer.assign(Ryan.begin(), Ryan.end());
            }
        }

        return;
    }
    if(arrow > info[idx]){
        Ryan[idx] = info[idx] + 1;
        arrow -= Ryan[idx];
    }
    for(int i = idx + 1; i<=10; i++){
        DFS(arrow, i, Ryan, info);
    }
}

int CalcDiff(vector<int> &Ryan, vector<int> &info){
    int ryan = 0; // 라이언 총 점수
    int apeach = 0; // 어피치 총 점수
    int diff; // 라이언, 어피치 점수 차
    for(int i = 0; i<=10; i++){
        int score = 10-i;
        if(Ryan[i] == 0 && info[i] == 0){
            continue;
        }
        if(Ryan[i] > info[i]){
            ryan += score;
        }
        else{
            apeach += score;
        }
    }
    diff = ryan-apeach;
    // 동점이거나 어피치가 더 큰 점수면 -1 반환
    if(diff <= 0){
        return -1;
    }
    return diff;
}

vector<int> solution(int n, vector<int> info) {  
    for(int i = 0; i<= 10; i++){
        vector<int> Ryan(11, 0); // 라이언 배열
        DFS(n, i, Ryan, info);
    }

    return answer;
}