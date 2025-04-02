#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;



bool solution(vector<string> phone_book) {
    bool answer = true;
    unordered_set<string> phonenum[21];
    for(auto &k: phone_book){
        phonenum[k.size()].insert(k);
    }
    
    for(int i = 20; i>0; i--){
        if(!phonenum[i].empty()){
            for(auto &k: phonenum[i]){
                for(int j = 1; j<k.size(); j++){
                    string s = "";
                    for(int l = 0; l<j; l++){
                        s.push_back(k[l]);
                    }
                    if(phonenum[j].find(s) != phonenum[j].end()){
                        return false;
                    }
                }
            }
        }
    }
    
    return answer;
}

// 길이 오름차순, 맨 앞 숫자 오름차순
// phonenum[길이] = {번호};
// phonenum[3] = {111, 222, 333};
// phonenum[5] = {11122, 12345, 53444, 99944};