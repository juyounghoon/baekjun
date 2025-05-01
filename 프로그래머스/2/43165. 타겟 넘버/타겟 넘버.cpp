#include <string>
#include <vector>

using namespace std;

int answer = 0;

// i: 현재 계산중인 index
// sum: numbers[i]까지 계산한 값
void DFS(vector<int> &numbers, int i, int num_size, int sum, int target){
    if(i == num_size){
        if(sum == target){
            ++answer;
        }
        return;
    }
    DFS(numbers, i+1, num_size, sum+numbers[i], target);
    DFS(numbers, i+1, num_size, sum-numbers[i], target);
}

int solution(vector<int> numbers, int target) {
    DFS(numbers, 0, numbers.size(), 0, target);
    
    return answer;
}