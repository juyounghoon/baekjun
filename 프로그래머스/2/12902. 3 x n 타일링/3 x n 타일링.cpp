#include <string>
#include <vector>

#define MAX 5000
#define MOD 1000000007
using namespace std;

long long solution(int n) {
    if(n%2) return 0;
    
    vector<long long> Table(MAX+1, -1);
    // f(0) = 1, f(2) = 3, f(n) = 4f(n-2) - f(n-4)
    Table[0] = 1;
    Table[2] = 3;
    for(int i = 4; i<=n; i += 2){
       Table[i] = (4 * Table[i - 2] % MOD - Table[i - 4] % MOD + MOD) % MOD;
    }
    
    return Table[n] % MOD;
}
