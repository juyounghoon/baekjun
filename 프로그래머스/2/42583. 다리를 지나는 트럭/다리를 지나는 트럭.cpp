#include <string>
#include <vector>
#include <queue>
using namespace std;

// bridge_length: 다리에 올라갈 수 있는 트럭의 최대 수
// weight: 다리에 올라갈 수 있는 트럭의 최대 무게
int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0; // 경과 시간
    int heavy = 0; // 현재 다리 위에 올라가 있는 트럭의 무게
    int count = truck_weights.size(); // 대기 트럭 수
    queue<pair<int, int>> q; // 다리 위에 있는 트럭을 큐로 표현 {트럭 무게, 다리에 올라간 시점}
    
    int i = 0; // 트럭 인덱스
    while(!(count == 0 && q.size() == 0)){
        answer++;
        //printf("현재 시각: %d  ", answer);
        if(!q.empty() && answer-q.front().second >= bridge_length){
            //printf("트럭 내림: %d  ", q.front().first);
            heavy -= q.front().first;
            q.pop();
        }
        if(count > 0 && q.size() < bridge_length && heavy + truck_weights[i] <= weight){
            //printf("트럭 올라감: %d  ", truck_weights[i]);
            heavy += truck_weights[i];
            q.push({truck_weights[i++], answer});
            count--;
        }
        //printf("\n");
    }
        
    return answer;
}
// push: 남아 있는 대기 트럭이 있고, 다리가 버틸 수 있을 때 push
// q.size() <= bridge_length 일 때 push 가능
// heavy <= weight 일 때 push 가능
// push 했으면 --count
// count == 0 && q.size() == 0 일 때까지 push, pop 반복 종료 조건
// pop: <트럭, 올라간 시간 기록> 현재시간 - 올라간 시간 >= bridge_length 이면 pop가능
// push와 pop은 동시에 가능 pop 먼저 하자.