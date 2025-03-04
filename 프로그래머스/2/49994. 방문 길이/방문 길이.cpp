#include <iostream>
#include <string>
#include <vector>
using namespace std;

pair<int, int> current = {0, 0}; // <x, y>
vector<vector<bool>> x_visit(11, vector<bool>(10, false));
vector<vector<bool>> y_visit(10, vector<bool>(11, false));
int cnt; // 새로운 길을 간 횟수

void Direction(char c){
    switch(c){
        case 'U':
            if(current.second < 5){
                if(!y_visit[-current.second+4][current.first+5]){
                    y_visit[-current.second+4][current.first+5] = true;
                    cnt++;
                }
                current.second++;
            }
            else{
                cout << "out range\n";
                break;
            }
            break;
        case 'D':
            if(current.second > -5){
                if(!y_visit[-current.second+5][current.first+5]){
                    y_visit[-current.second+5][current.first+5] = true;
                    cnt++;
                }
                current.second--;
            }
            else{
                cout << "out range\n";
                break;
            }
            break;
        case 'R':
            if(current.first < 5){
                if(!x_visit[-current.second+5][current.first+5]){
                    x_visit[-current.second+5][current.first+5] = true;
                    cnt++;
                }
                current.first++;
            }
            else{
                cout << "out range\n";
                break;
            }
            break;
        case 'L':
            if(current.first > -5){
                if(!x_visit[-current.second+5][current.first+4]){
                    x_visit[-current.second+5][current.first+4] = true;
                    cnt++;
                }
                current.first--;
            }
            else{
                cout << "out range\n";
                break;
            }
            break;
        default:
            break;
            
    }
}

int solution(string dirs) {
    int answer = 0;
    vector<char> input(dirs.begin(), dirs.end());
    for(auto &k: input){
        Direction(k);
    }
    answer = cnt;
    return answer;
}