#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int L, C;
vector<char> v;

void MakeComb(int index, int cnt, vector<char>& comb);
bool CheckJaMo(vector<char> comb);

int main(){
    cin >> L >> C;
    char input;
    for(int i = 0; i<C; i++){
        cin >> input;
        v.push_back(input);
    }
    sort(v.begin(), v.end());
    
    vector<char> comb;
    MakeComb(0, 0, comb);

    return 0;
}

void MakeComb(int index, int cnt, vector<char>& comb){
    if(cnt >= L){
        if(CheckJaMo(comb)){
            for(int i = 0; i<L; i++){
                cout << comb[i];
            }
            cout << "\n";
        }
        return;
    }

    for(int i = index; i<C; i++){
        comb.push_back(v[i]);
        MakeComb(i+1, cnt+1, comb);
        comb.pop_back();
    }
}

bool CheckJaMo(vector<char> comb){
    bool ret = false;
    int cnt_ja = 0; // 2개 이상
    int cnt_mo = 0; // 1개 이상
    for(int i = 0; i<comb.size(); i++){
        // a e i o u
        if(comb[i] == 'a' || comb[i] == 'e'|| comb[i] == 'i' || comb[i] == 'o' || comb[i] == 'u'){
            cnt_mo++;
        }
        else{
            cnt_ja++;
        }
    }
    if(cnt_ja >= 2 && cnt_mo >= 1){
        ret = true;
    }

    return ret;
}