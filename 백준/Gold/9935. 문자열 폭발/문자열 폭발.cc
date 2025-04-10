#include <iostream>
#include <string>

using namespace std;

string str, bomb;

int main(){
    cin >> str >> bomb;

    string total;
    for(int i = 0; i<str.size(); i++){
        total.push_back(str[i]);
        string temp;
        temp.assign(total.end()-bomb.size(), total.end());
        if(temp == bomb){
            for(int j = 0; j<bomb.size(); j++){
                total.pop_back();
            }
        }
    }
    if(total.size() == 0){
        cout << "FRULA";
    }
    else{
        cout << total;
    }

    return 0;
}