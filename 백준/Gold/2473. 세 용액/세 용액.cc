#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long MinSum = 3000000000;

long long abs_val(long long a){
    return a<0 ? -a : a;
}

int main(){
    int N;
    cin >> N;
    vector<long long> liquid(N);
    vector<long long> answer(3);

    for(int i = 0; i<N; i++){
        cin >> liquid[i];
    }
    sort(liquid.begin(), liquid.end());

    int left = 0, right = N-1;

    for(int i = 0; i<N-2; i++){
        int left = i+1, right = N-1;
        while(left < right){
            long long sum = liquid[i] + liquid[left] + liquid[right];
            if(MinSum > abs_val(sum)){
                MinSum = abs_val(sum);
                answer[0] = liquid[i];
                answer[1] = liquid[left];
                answer[2] = liquid[right];
            }
            if(sum < 0) left++;
            else right--;
        }
    }
    printf("%lld %lld %lld\n", answer[0], answer[1], answer[2]);

    return 0;
}