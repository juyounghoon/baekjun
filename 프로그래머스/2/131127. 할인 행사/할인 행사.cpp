#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// want: 정현이가 원하는 제품
// number: 정현이가 원하는 제품 수
// discount: 마트에서 할인하는 제품

int stringtoint(string s){
    int ret = 0;
    int p = 1;
    int m = 1000000007;
    for(int i = 0; i<s.size(); i++){
        ret += s[i]*p;
        p += 31;
    }
    return ret % m;
}

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    
    vector<int> discounttoint;
    for(int i = 0; i<discount.size(); i++){
        discounttoint.push_back(stringtoint(discount[i]));
    }
    
    unordered_map<int, int> jjung; // <물건, 수>
    for(int i = 0; i<want.size(); i++){
        jjung[stringtoint(want[i])] = number[i];
    }
    
    unordered_map<int, int> jjung_temp;
    for(int i = 0; i<= discount.size() - 10; i++){
        jjung_temp = jjung;
        for(int j = i; j < i + 10; j++){
            if(jjung_temp.find(discounttoint[j]) != jjung_temp.end()){
                --jjung_temp[discounttoint[j]];
            }
        }
        
        ++answer;
        for(const auto &k: jjung_temp){
            if(k.second != 0){
                --answer;
                break;
            }
        }
    }
    return answer;
}