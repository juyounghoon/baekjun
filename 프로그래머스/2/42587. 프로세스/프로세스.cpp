#include <string>
#include <vector>
#include <queue>

using namespace std;

int Find_MaxPrio(queue<pair<int, int>> q){
    int max = 0;
    while(!q.empty()){
        if(q.front().second > max) max = q.front().second;
        q.pop();
    }
    
    return max;
}

int solution(vector<int> priorities, int location) {
    int answer = 0;
    
    int max_prio = 1;
    
    queue<pair<int, int>> q; // <PID(인덱스), prio>
    for(int i = 0; i<priorities.size(); i++){
        if(priorities[i] > max_prio) max_prio = priorities[i];
        q.push({i, priorities[i]});
    }

    int order = 0;
    while(!q.empty()){
        int loc = q.front().first;
        int prio = q.front().second;
        q.pop();
        if(prio == max_prio){
            order++;
            if(loc == location){
                break;
            }
            max_prio = Find_MaxPrio(q);
            continue;
        }
        q.push({loc, prio});
    }
    answer = order;
    return answer;
}