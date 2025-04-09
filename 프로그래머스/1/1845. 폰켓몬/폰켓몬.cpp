#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    int N = nums.size();
    vector<int> pkm;
    sort(nums.begin(), nums.end());
    pkm.push_back(nums[0]);
    for(int i = 1; i<N; i++){
        if(nums[i] != nums[i-1]){
            pkm.push_back(nums[i]);
        }
    }
    if(pkm.size() < N/2){
        answer = pkm.size();
    }
    else{
        answer = N/2;
    }
    return answer;
}