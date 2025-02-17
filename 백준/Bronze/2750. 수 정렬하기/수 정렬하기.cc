#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int N;
    int* arr;
    cin >> N;
    arr = new int[N];
    int tmp;
    for(int i = 0; i< N; i++){
        cin >> tmp;
        arr[i] = tmp;
    }
    sort(arr, arr + N);
    for(int i = 0; i < N; i++){
        cout << arr[i] << endl;
    }
}