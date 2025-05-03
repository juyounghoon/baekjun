#include <iostream>
#include <string>

using namespace std;


int main(){
    int M;
    int S = 0; // 비트마스크 집합 S(1~20)

    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> M;
    for(int i = 0; i<M; i++){
        string input;
        int x;
        cin >> input;

        if(input == "add"){
            cin >> x;
            S |= (1<<x);
        }
        else if(input == "remove"){
            cin >> x;
            S &= ~(1<<x);
        }
        else if(input == "check"){
            cin >> x;
            cout << ((S & (1<<x)) ? 1 : 0) << "\n";
        }
        else if(input == "toggle"){
            cin >> x;
            S ^= (1<<x);
        }
        else if(input == "all"){
            S |= (1<<21) - 1;
        }
        else if(input == "empty"){
            S = 0;
        }
    }

    return 0;
}