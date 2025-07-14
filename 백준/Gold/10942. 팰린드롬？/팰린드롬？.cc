#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> Palindrome;
/*
Pal[1][2]: S가 1, E가 2일 때 팰린드롬인지?
Pal[m][n]가 true면 arr[m-1] == arr[n+1] 이면 Pal[m-1][n+1]도 true
    => isPalidrome: arr[s] == arr[e] 이면 Pal[s+1][e-1] 확인

*/

// 시간복잡도: E-S
bool isPalindrome(const vector<int> &arr, int S, int E){
    if(S == E) return true;
    else if(E-S == 1){
        if(arr[S] == arr[E]) return true;
        else return false;
    }
    else{
        if(arr[S] == arr[E]){
            if(Palindrome[S+1][E-1] == 1) return true;
            else if(Palindrome[S+1][E-1] == 0) return false;
        }
    }

    return false;
}

int main(){
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N;
    Palindrome.resize(N+1, vector<int>(N+1, -1));
    vector<int> arr(N+1);
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
    }
    
    // 길이가 i개 짜리, 시작 인덱스가 s, 끝 인덱스가 e
    for(int i = 1; i<=N; i++){
        for(int s = 1, e = s+i-1; e<=N; s++, e++){
            //cout << s << " " << e << endl;
            if(isPalindrome(arr, s, e)){
                Palindrome[s][e] = 1;
            }
            else{
                Palindrome[s][e] = 0;
            }

        }
    }

    int S, E;
    cin >> M;
    for(int i = 0; i < M; i++){
        cin >> S >> E;
        if(Palindrome[S][E] == 1){
            cout << 1 << "\n";
        }
        else if(Palindrome[S][E] == 0){
            cout << 0 << "\n";
        }
    }

    return 0;
}

/*
1: 2000
2: 1999
3: 1998
4: 1997
...
1999: 1~1999 2~2000 2

 */