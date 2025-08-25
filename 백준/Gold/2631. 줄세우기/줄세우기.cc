#include <iostream>
#include <vector>

using namespace std;

int N;
vector<int> input;

// num을 LIS에 삽입. 자신보다 큰 수 중 가장 작은 수 위치에 삽입.
void BinarySearch(vector<int> &LIS, int num){
    int start = 0;
    int end = LIS.size()-1;
    int mid = (start+end)/2;

    if(LIS[LIS.size()-1]<num){
        LIS.push_back(num);
        return;
    }

    while(start<end){
        if(LIS[mid]<num){
            start = mid+1;
        }
        else{
            end = mid;
        }
        mid = (start+end)/2;
    }
    LIS[start] = num;
}

int main(){
    cin >> N;
    for(int i = 0; i<N; i++){
        int tmp; cin >> tmp;
        input.push_back(tmp);
    }
    
    vector<int> LIS;
    LIS.push_back(input[0]);
    for(int i = 1; i<N; i++){
        BinarySearch(LIS, input[i]);
    }

    cout << N - LIS.size();

    return 0;
}