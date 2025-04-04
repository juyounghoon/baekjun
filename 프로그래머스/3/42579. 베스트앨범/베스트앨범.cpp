#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <tuple>

using namespace std;

// 0. 장르 별 2곡씩
// 1. 많이 재생된 장르 먼저
// 2. 같은 장르 내에서는 많이 재생된 노래먼저
// 3. 같은 장르, 같은 재생 수이면 고유번호 낮은 노래먼저

bool cmp(pair<string, int> a, pair<string, int> b){
    return a.second > b.second;
}

bool cmp_t(tuple<int, int, int> a, tuple<int, int, int> b){
    if(get<0>(a) == get<0>(b)){
        if(get<1>(a) == get<1>(b)){
            return get<2>(a) < get<2>(b);
        }
        else{
            return get<1>(a) > get<1>(b);
        }
    }
    else{
        return get<0>(a) < get<0>(b);
    }
} 

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    
    // 장르 순위 정하기
    map<string, int> tot_plays; // [장르] = 재생횟수
    for(int i = 0; i<genres.size(); i++){
        tot_plays[genres[i]] += plays[i];
    }
    vector<pair<string, int>> genres_rank; // [rank] = {장르, 재생횟수}
    for(const auto &[k, v]: tot_plays){
        genres_rank.push_back({k, v});
    }
    sort(genres_rank.begin(), genres_rank.end(), cmp);
    
    //vector<int, pair<int, int>> song; // [] = {장르(랭킹으로 표현), 재생횟수, 고유번호}
    
    vector<int> genr(genres.size()); // 랭킹으로 표현한 장르
    for(int i = 0; i<genres.size(); i++){
        for(int j = 0; j<genres_rank.size(); j++){
            if(genres_rank[j].first == genres[i]){
                genr[i] = j;
            }
        }
    }
    vector<tuple<int, int, int>> songs(genres.size()); // {장르(랭킹), 재생횟수, 고유번호}
    for(int i = 0; i<genres.size(); i++){
        songs[i] = {genr[i], plays[i], i};
    }
    sort(songs.begin(), songs.end(), cmp_t);
    
    /*
    for(const auto &k: songs){
        cout << get<0>(k) << " " << get<1>(k) << " " << get<2>(k)<< endl;
    }
    */
    
    map <int, int> count; // <장르, 카운트>
    for(const auto &k: songs){
        if(count[get<0>(k)] < 2){
            answer.push_back(get<2>(k));
            count[get<0>(k)]++;
        }
    }
    
    return answer;
}

// 장르 순위 정하고
// 장르에서 두 곡 뽑고, 한 곡만 있으면 한 곡만
// 정렬