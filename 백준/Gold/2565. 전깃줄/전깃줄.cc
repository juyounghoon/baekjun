#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> input;

void BinarySearch(vector<int> &LIS, int num, int &cnt){
    int s = 0;
    int e = cnt-1;
    if(LIS[e]<num){
        LIS[cnt++] = num;
        return;
    }
    while(s<=e){
        int m = (s+e)/2;
        if(LIS[m]<num) s = m+1;
        else if(num <= LIS[m]) e = m-1;
    }
    LIS[s] = num;
}

int main(){
    int x;
    cin >> x;
    for(int i = 0; i<x; i++){
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;
        input.push_back({tmp1, tmp2});
    }
    sort(input.begin(), input.end());
    vector<int> LIS(x);
    int cnt = 0;
    LIS[cnt++] = input[0].second;
    for(int i = 1; i<x; i++){
        BinarySearch(LIS, input[i].second, cnt);
    }
    cout << x-cnt;

    return 0;
}