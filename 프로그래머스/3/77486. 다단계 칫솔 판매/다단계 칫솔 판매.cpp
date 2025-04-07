#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;
    answer.resize(enroll.size());
    
    unordered_map<string, int> nametoint; // 이름을 가입순으로 인덱스로 변환(center는 0)
    vector<int> tree; // tree[자식] = 부모
    tree.resize(enroll.size()+1);
    
    vector<int> money; // 각자 수익금(center 포함)
    money.resize(enroll.size()+1);
    
    for(int i = 0; i<enroll.size(); i++){
        nametoint[enroll[i]] = i+1;
    }
    
    // tree[자식] = 부모
    // enroll: 자식, referral: 부모
    for(int i = 0; i<referral.size(); i++){
        int child = nametoint[enroll[i]];
        int parent;
        if(referral[i] == "-"){
            parent = 0;
        }
        else{
            parent = nametoint[referral[i]];
        }
        tree[child] = parent;
    }
    
    for(int i = 0; i<seller.size(); i++){
        int who = nametoint[seller[i]];
        int howmuch = amount[i] * 100;
        
        while(who){
            int sangnap = (int)(howmuch * 0.1);
            int mymoney = howmuch - sangnap;
            
            money[who] += mymoney;
            who = tree[who];
            howmuch = sangnap;
        }
    }

    for(int i = 0; i<answer.size(); i++){
        answer[i] = money[i+1];
    }
    
    return answer;
}