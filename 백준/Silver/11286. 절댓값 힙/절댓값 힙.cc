#include <iostream>
#include <queue>

using namespace std;

int N;

struct Compare{
    bool operator ()(pair<int, int> a, pair<int, int> b){
        if(a.first == b.first){
            return a.second > b.second;
        }
        return a.first > b.first;
    }
};

priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq; // <절댓값, 입력값>
int PopPQ();

int main(){
    cin >> N;
    int input;
    for(int i = 0; i<N; i++){
        cin >> input;
        if(input != 0){
            if(input < 0){
                pq.push(make_pair(-input, input));
            }
            else{
                pq.push(make_pair(input, input));
    
            }
        }
        else{
            cout << PopPQ() << "\n";
        }
    }

    return 0;
}

int PopPQ(){
    int ret;
    if(pq.empty()){
        ret = 0;
    }
    else{
        ret = pq.top().second;
        pq.pop();
    }

    return ret;
}