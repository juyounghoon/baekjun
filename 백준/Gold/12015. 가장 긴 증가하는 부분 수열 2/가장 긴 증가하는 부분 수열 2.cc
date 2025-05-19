#include <iostream>
#include <vector>

using namespace std;

void BinarySearch(int num, vector<int> &answer, int &cnt){
    int start = 0;
    int end = cnt-1;
    int mid = (start + end) / 2;
    if(num > answer[cnt-1]){
        answer[cnt++] = num;
        return;
    }

    while(start < end){
        mid = (start + end) / 2;
        if(answer[mid] < num){
            start = mid + 1;
        }
        else if(answer[mid] > num){
            end = mid;
        }
        else{
            answer[mid] = num;
            return;
        }
    }
    answer[start] = num;
}

int main(){
    int N;
    cin >> N;
    vector<int> arr(N);
    vector<int> answer(N);
    for(int i = 0; i<N; i++){
        cin >> arr[i];
    }
    int cnt = 0;
    answer[cnt++] = arr[0];

    for(int i = 1; i<N; i++){
        BinarySearch(arr[i], answer, cnt);
    }
    cout << cnt;
    return 0;
}