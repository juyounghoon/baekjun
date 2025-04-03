#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
// record: 채팅방 로그
// Enter [유저 아이디] [닉네임]
// Leave [유저 아이디]
// Change [유저 아이디] [닉네임]

vector<string> solution(vector<string> record) {
    vector<string> answer;
    
    // key(아이디) = value(닉네임) 형식으로 데이터베이스 생성
    unordered_map<string, string> user; // <유저 아이디, 닉네임>
    for(int i = 0; i<record.size(); i++){
        if(record[i][0] == 'E'){
            string id;
            string nickname;
            
            // record에 있는 id, nickname 읽기
            int j = 6;
            while(record[i][j] != ' '){
                id.push_back(record[i][j]);
                ++j;
            }
            while(j < record[i].size()){
                nickname.push_back(record[i][j]);
                ++j;
            }
            
            // 처음 들어온 사람이던, 들어왔다가 나간 후 이름 바꾼 사람이던
            user[id] = nickname;
        }
        
        if(record[i][0] == 'C'){
            string id;
            string nickname;
            
            // record에 있는 id, nickname 읽기
            int j = 7;
            while(record[i][j] != ' '){
                id.push_back(record[i][j]);
                ++j;
            }
            while(j < record[i].size()){
                nickname.push_back(record[i][j]);
                ++j;
            }
            user[id] = nickname;
        }
    }

    /*
    for(const auto &k: user){
        cout << k.first << ":" << k.second << endl;
    }
    */
    
    // Enter, Leave만 최종 출력
    for(int i = 0; i<record.size(); i++){
        string log;
        string id;
        if(record[i][0] == 'E'){
            int j = 6;
            while(record[i][j] != ' '){
                id.push_back(record[i][j]);
                ++j;
            }
            log = user[id];
            log.append("님이 들어왔습니다.");
            log.erase(0, 1);
            answer.push_back(log);
        }
        else if(record[i][0] == 'L'){
            int j = 6;
            while(j < record[i].size()){
                id.push_back(record[i][j]);
                ++j;
            }
            log = user[id];
            log.append("님이 나갔습니다.");
            log.erase(0, 1);
            answer.push_back(log);
        }
    }
    
    return answer;
}