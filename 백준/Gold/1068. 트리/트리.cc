#include <iostream>
#include <vector>
#include <set>

using namespace std;

int cnt;

void DeleteNode(vector<set<int>> &tree, set<int> &first_nodes, int del){
    for(int node: first_nodes){
        if(node == del){
            first_nodes.erase(node);
            return;
        }
    }

    for(int i = 0; ;i++){
        for(int n: tree[i]){
            if(n == del){
                tree[i].erase(del);
                return;
            }
        }
    }
}

bool isLeaf(const vector<set<int>> &tree, int node){
    bool ret;
    if(tree[node].empty()){
        ret = true;
    }
    else{
        ret = false;
    }
    return ret;
}

void TravelTree(const vector<set<int>> &tree, int node){
    if(isLeaf(tree, node)) cnt++;
    else{
        for(int next: tree[node]){
            TravelTree(tree, next);
        }
    }
}

int main(){
    int N, del;
    cin >> N;
    vector<set<int>> tree(N); // [parent] = {child1, child2, child3, ...}
    set<int> first_nodes;
    for(int node = 0; node<N; node++){
        int parent;
        cin >> parent;
        if(parent == -1){
            first_nodes.insert(node);
        }
        else{
            tree[parent].insert(node);
        }
    }
    cin >> del;

    DeleteNode(tree, first_nodes, del);
    for(int node: first_nodes){
        TravelTree(tree, node);
    }
    cout << cnt;

    return 0;
}