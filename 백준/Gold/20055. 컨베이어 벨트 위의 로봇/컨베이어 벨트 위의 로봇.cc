#include <iostream>
#include <vector>

using namespace std;

int N;
int K;

int main(){
    int CntStep = 0;
    int CntZero = 0;
    cin >> N >> K;
    vector<int> A(2*N);
    vector<bool> isAload(2*N, false);
    for(int i = 0; i<2*N; i++){
        cin >> A[i];
    }
    int load = 0;
    int unload = N-1;
    while(CntZero<K){
        CntStep++;
        // 벨트 회전
        load = (load-1 + 2*N)%(2*N);
        unload = (unload-1 + 2*N)%(2*N);
        if(isAload[unload]){
            isAload[unload] = false;
        }

        // 로봇 이동
        int i = (unload-1+2*N)%(2*N);
        while(true){
            int front = (i+1+2*N)%(2*N);
            if(isAload[i] && !isAload[front] && A[front] > 0){
                isAload[i] = false;
                isAload[front] = true;
                A[front]--;
                if(front == unload) isAload[front] = false;
                if(A[front] == 0) CntZero++;
            }
            i = (i-1+2*N)%(2*N);
            if(i == load) break;
        }

        // 로봇 load
        if(A[load]>0){
            A[load]--;
            if(A[load] == 0) CntZero++;
            isAload[load] = true;
        }
    }
    cout << CntStep;

    return 0;
}