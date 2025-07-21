#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int ans;
vector<int> drink;
vector<vector<int>> Maximum; // [n][0]: ox일때 max, [n][1]: xo일 때 max, [n][2]: oo일 때 max [n][3]: xx일 때 max

int main(){
    cin >> n;
    drink = vector<int>(n+1, 0);
    Maximum = vector<vector<int>>(n+1, vector<int>(4));
    for(int i = 1; i<=n; i++){
        cin >> drink[i];
    }
    Maximum[0][0] = 0;
    Maximum[0][1] = 0;
    Maximum[0][2] = 0;
    Maximum[0][3] = 0;

    Maximum[1][0] = 0;
    Maximum[1][1] = drink[1];
    Maximum[1][2] = drink[1];
    Maximum[1][3] = 0;
    
    if(n>1){
        Maximum[2][0] = drink[1];
        Maximum[2][1] = drink[2];
        Maximum[2][2] = drink[1] + drink[2];
        Maximum[2][3] = 0;
    }
    
    if(n>2){
        for(int i = 3; i<=n; i++){
            Maximum[i][0] = max(Maximum[i-1][2], Maximum[i-1][1]);
            Maximum[i][1] = max(Maximum[i-1][0] + drink[i], Maximum[i-1][3] + drink[i]);
            Maximum[i][2] = Maximum[i-1][1] + drink[i];
            Maximum[i][3] = max(Maximum[i-1][0], Maximum[i-1][3]);
        }
    }

    for(int i = 0; i<4; i++){
        if(ans < Maximum[n][i]) ans = Maximum[n][i];
    }
    cout << ans;
    return 0;
}
/*
[n][0] = [n-1][2], [n-1][1] 중 max
[n][1] = [n-1][0] + d[n], [n-1][3] + d[n] 중 max
[n][2] = [n-1][1] + d[n]
[n][3] = [n-1][0], [n-1][3] 중 max
*/