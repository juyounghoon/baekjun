#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;
    /*
    for(int i = 1; i<n+1; i++){
        int k = 0;
        for(k = 0; k<i; k++){
            arr[i-1][k] = i;
        }
        for(int j = k; j<n+1; j++){
            arr[i-1][j-1] = j;
        }
    }
    */
    // arr[y][x]
    int y_left = left/n + 1;
    int x_left = left - n*(left/n) + 1;
    
    int y_right = right/n + 1;
    int x_right = right - n*(right/n) + 1;
    //printf("[%d][%d] ~ [%d][%d]\n",y_left, x_left, y_right, x_right);
    for(int i = y_left; i < y_right+1; i++){
        static int k = x_left;
        int loop_k = i+1;
        int loop_j = n+1;
        if(i == y_right){
            //printf(" 마지막 줄(%d)\n", i);
            if(x_right<i+1){
                loop_k = x_right+1;
            }
            loop_j = x_right+1;
        }
        for(; k<loop_k;k++){
            //printf("[반복 loop_k: %d k: %d, i: %d]\n", loop_k, k, i);
            answer.push_back(i);
        }
        //printf("k는 %d, loop_j는 %d\n",k, loop_j);
        for(int j = k; j < loop_j; j++){
            //printf(" k: %d j: %d loop_j: %d ",k, j, loop_j);
            answer.push_back(j);
        }
        cout << endl;
        k = 1;
    }
    /*
    vector<int> flat; // 2차원 배열을 flatening 할 1차원 배열
    for(int i = 1; i<n+1; i++){
        int k = 1;
        for(; k<i+1; k++){
            flat.push_back(i);
        }
        for(int j = k; j<n+1; j++){
            flat.push_back(j);
        }
    }
    */
    return answer;
}