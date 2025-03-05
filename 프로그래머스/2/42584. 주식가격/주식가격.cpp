#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer;
    answer.resize(prices.size(), 0);
    stack<int> st;
    for(int i = 0; i<prices.size(); i++){
        // 오름차순일 때까지 pop
        // top이 작으면 pop
        // top이 크거나 같으면 멈추고 push
        while(!st.empty() && prices[st.top()] > prices[i]){
            answer[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }
    while(!st.empty()){
        answer[st.top()] = prices.size() - st.top() - 1;
        st.pop();
    }
    
    return answer;
}

/*
1
*/