#include <iostream>
#include <vector>

using namespace std;

#define MAX 2000000000
int MinSum = MAX;

int abs(int a){
    return a<0 ? -a : a;
}

int main(){
    int N;
    cin >> N;
    vector<int> liquid(N);
    pair<int, int> answer;
    
    for(int i = 0; i<N; i++){
        cin >> liquid[i];
    }

    int left = 0, right = N-1;

    while(left < right){
        int sum = liquid[left] + liquid[right];
        if(MinSum > abs(sum)){
            MinSum = abs(sum);
            answer = {liquid[left], liquid[right]};
        }
        if(sum < 0) left++;
        else right--;
    }
    printf("%d %d", answer.first, answer.second);
    return 0;
}