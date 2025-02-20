// 오큰수
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// 스택 사용
// 스택에 인덱스와 입력 저장 <인덱스, 입력>
// top보다 같거나 작으면 push
// top보다 크면 pop. 자신보다 크거나 같은 수가 나오면 pop 멈추고 push
// pop하면서 pop한 인덱스와 동일한 인덱스를 갖는 출력할 배열에 비교할 값 저장

int N;
stack<pair<int, int> > s;
int* map; // 출력할 정답 배열

int main(){
    cin >> N;
    map = new int[N];
    //일단 -1로 초기화
    for(int i = 0; i<N; i++){
        map[i] = -1;
    }

    int input;
    for(int i = 0; i<N; i++){
        cin >> input;
        while(!s.empty() && !(s.top().second >= input)){
            map[s.top().first] = input;
            s.pop();
        }
        s.push(make_pair(i, input));
    }

    // 정답 출력
    for(int i = 0; i<N; i++){
        cout << map[i] << " ";
    }
    return 0;
}