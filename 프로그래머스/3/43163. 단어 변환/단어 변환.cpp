#include <string>
#include <vector>
#include <queue>

using namespace std;

#define MAX 1000000

// 두 문자열의 알파벳 차이를 구하는 함수
int Find_Diff(string a, string b){
    int diff = 0;
    for(int i = 0; i<a.size(); ++i){
        if(a[i] != b[i]) ++diff;
    }
    return diff;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    int destination = MAX;
    
    for(int i = 0; i<words.size(); i++){
        if(words[i] == target){
            destination = i+1;
            break;
        }
    }
    if(destination == MAX){
        return 0;
    }
    
    // 그래프 생성 및 초기화
    vector<vector<int>> graph(words.size()+1); // [0]: begin, [destination]: target
    for(int i = 0; i<words.size(); i++){
        if(Find_Diff(begin, words[i]) == 1){
            graph[0].push_back(i+1);
            graph[i+1].push_back(0);
        }
    }
    for(int i = 0; i<words.size(); ++i){
        for(int j = i+1; j<words.size(); ++j){
            if(Find_Diff(words[i], words[j]) == 1){
                graph[i+1].push_back(j+1);
                graph[j+1].push_back(i+1);
            }
        }
    }
    
    // 그래프 순회하면서 destination까지 최소 거리 구하기
    queue<pair<int, int>> q; // <현재 노드, 거리>
    vector<int> distance(words.size()+1, MAX);
    q.push({0, 0});
    while(!q.empty()){
        int n = q.front().first;
        int d = q.front().second;
        q.pop();
        for(const int &next: graph[n]){
            if(d+1 < distance[next]){
                distance[next] = d+1;
                printf("%d: %d\n",next, distance[next]);
                q.push({next, d+1});
            }
        }
    }
    answer = distance[destination];
    if(answer == MAX) answer = 0;
    
    return answer;
}