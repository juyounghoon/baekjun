#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> sizes) {
    int answer = 0;
    vector<int> width(sizes.size());
    vector<int> height(sizes.size());
    for(int i = 0; i<sizes.size(); i++){
        if(sizes[i][0] > sizes[i][1]){
            width[i] = sizes[i][0];
            height[i] = sizes[i][1];
        }
        else{
            width[i] = sizes[i][1];
            height[i] = sizes[i][0];
        }
    }
    int max_width = *max_element(width.begin(), width.end());
    int max_height = *max_element(height.begin(), height.end());
    answer = max_width*max_height;
    
    return answer;
}