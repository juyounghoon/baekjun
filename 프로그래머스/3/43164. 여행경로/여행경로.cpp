#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

multiset<pair<string, string>> mset;
string best_path;

void DFS(string dep, int cnt, vector<bool> visited, string deplist){
    int i = 0;
    for(auto it = mset.begin(); it != mset.end(); ++it, ++i){
        // 출발지가 dep과 같으면서 안 쓴 티켓
        if(it->first == dep && visited[i] == false){
            visited[i] = true;
            dep = it->second;
            deplist += dep;
            DFS(dep, cnt+1, visited, deplist);
            visited[i] = false;
            dep = it->first;
            deplist.pop_back();
            deplist.pop_back();
            deplist.pop_back();
        }
    }
    
    // 티켓을 다 써버린 경우
     if(cnt == mset.size() && deplist < best_path){
         best_path = deplist;
     }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    vector<bool> visited(tickets.size(), false);
    string dep = "ICN";
    string deplist = "ICN";
    
    // ticket을 multiset으로 재정렬
    for(const auto &ticket: tickets){
        mset.insert({ticket[0], ticket[1]});
    }
    
    for(int i = 0; i<=tickets.size(); i++){
        best_path += "ZZZ";
    }
    DFS("ICN", 0, visited, deplist);

    string tmp;
    for(int i = 0; i<best_path.size(); i++){
        tmp.push_back(best_path[i]);
        if(tmp.size() == 3){
            answer.push_back(tmp);
            tmp.clear();
        }
    }
    
    return answer;
}