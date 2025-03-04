#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;

    // arr[y][x]
    int y_left = left/n + 1;
    int x_left = left%n + 1;
    
    int y_right = right/n + 1;
    int x_right = right%n +1;
    for(int i = y_left; i < y_right+1; i++){
        static int k = x_left;
        int loop_k = i+1;
        int loop_j = n+1;
        
        // 마지막 줄
        if(i == y_right){
            if(x_right<i+1){
                loop_k = x_right+1;
            }
            loop_j = x_right+1;
        }
        
        for(; k<loop_k;k++){
            answer.push_back(i);
        }
        
        for(int j = k; j < loop_j; j++){

            answer.push_back(j);
        }
        k = 1;
    }
    return answer;
}