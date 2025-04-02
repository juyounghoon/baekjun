#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int nametoint(string name){
    int ret = 0;
    int length = name.size();
    int p = 1;
    int m = 100000007;
    for(int i = 0; i<length; i++){
        ret += name[i]*p;
        p *= 31;
    }
    return ret % m;
}

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    map<int, pair<int, string>> p; // <참가자이름int, <중복 수, 본명>>
    
    for(auto &k: participant){
        int name = nametoint(k);
        if(p.find(name) != p.end()){
            p[name].first++;
            
        }
        else{
            p[name] = {1, k};
        }
    }
    
    /*
    cout << "map 출력";
    cout << endl;
    for(auto &k: p){
        cout << k.first;
        cout << " ";
        cout << k.second.first;
        cout << ", ";
        cout << k.second.second;
        cout << "\n";
    }
    */
    
    
    for(auto &k: completion){
        int name = nametoint(k);
        p[name].first--;
    }
    
    for(auto &k: p){
        if(k.second.first > 0){
            answer = k.second.second;
            break;
        }
    }

    return answer;
}