#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> arr, int divisor) {
    vector<int> answer;
    for(auto &k: arr){
        int remain = k % divisor; // 나머지
        if(remain == 0){
            answer.push_back(k);
        }
    }
    if(answer.size() == 0){
        answer.push_back(-1);
    }
    sort(answer.begin(), answer.end());
    return answer;
}