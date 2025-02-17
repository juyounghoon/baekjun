#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct People{
    int age;
    string name;
}People;


bool Compare(const People& a, const People& b){
    return a.age < b.age;
}

int main(){
    int N;
    vector<People> p;
    cin >> N;
    People tmp;
    for(int i = 0; i<N; i++){
        cin >> tmp.age >> tmp.name;
        p.push_back(tmp);
    }
    stable_sort(p.begin(), p.end(), Compare);

    for(auto &k:p){
        cout << k.age << " "<< k.name << "\n";
    }
    return 0;
}