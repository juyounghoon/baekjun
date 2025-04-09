#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<bool> visit;

bool cmp(int a, int b){
    return a < b;
}

int solution(vector<int> people, int limit) {
    int answer = 0;
    int size = people.size();
    vector<bool> visit(size, false);
    
    sort(people.begin(), people.end());
    // 0 ~ size-1
    for(int i = 0, j = size-1; i<size; i++){
        if(!visit[i]){
            while(j > i){
                if(people[i] + people[j] <= limit){
                    visit[j] = true;
                    j--;
                    break;
                }
                else{
                    j--;
                }
            }
            visit[i] = true;
            answer++;
        }
    }
    
    return answer;
}
