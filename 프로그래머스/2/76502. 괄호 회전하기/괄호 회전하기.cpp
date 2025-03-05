#include <string>
#include <vector>
#include <stack>

using namespace std;

bool isRight(string s){
    stack<char> stk;
    for(char &c: s){
        if(c == '('){
            stk.push(c);
        }
        else if(c == ')' && stk.top() == '('){
            stk.pop();
        }
        else if(c == '{'){
            stk.push(c);
        }
        else if(c == '}' && stk.top() == '{'){
                stk.pop();
        }
        else if(c == '['){
            stk.push(c);
        }
        else if(c == ']' && stk.top() == '['){
                stk.pop();
        }
        else{
            return false;
        }
    }
    
    return stk.empty();
}

int solution(string s) {
    int answer = 0;
    for(int i = 0; i<s.length(); i++){
        char end = s[0];
        s.assign(s.begin() + 1, s.end());
        s.push_back(end);
        if(isRight(s)){
            answer++;
        }
    }
    return answer;
}