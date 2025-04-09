#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>

using namespace std;

typedef struct Treenode{
    int x;
    int y;
    int data;
    Treenode* left;
    Treenode* right;
    
    Treenode(int a, int b, int value) : x(a), y(b), data(value), left(nullptr), right(nullptr) {}
} Treenode;

vector<int> pre_array;
vector<int> post_array;
vector<bool> visit;

void MakeTree(Treenode* current, Treenode* node);
void MakeTree(Treenode* current, Treenode* node){
    if(current->x < node->x){
        if(current->right != nullptr){
            current = current->right;
            MakeTree(current, node);
        }
        else{
            current->right = node;
        }
    }
    else{
        if(current->left != nullptr){
            current = current->left;
            MakeTree(current, node);
        }
        else{
            current->left = node;
        }
    }
}

void PrintTree(Treenode* node){
    cout << node->data;
    if(node->left != nullptr){
        Treenode* current = node->left;
        PrintTree(current);
    }
    if(node->right != nullptr){
        Treenode* current = node->right;
        PrintTree(current);
    }
}

void Preorder(Treenode* node){
    pre_array.push_back(node->data);
    if(node->left != nullptr){
        Treenode* current = node->left;
        Preorder(current);
    }
    if(node->right != nullptr){
        Treenode* current = node->right;
        Preorder(current);
    }
}

void Postorder(Treenode* node){
    if(node->left != nullptr){
        Treenode* current = node->left;
        Postorder(current);
    }
    if(node->right != nullptr){
        Treenode* current = node->right;
        Postorder(current);
    }
    post_array.push_back(node->data);
}

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
    if(a.first.second == b.first.second){
        return a.first.first < b.first.first;
    }
    else{
        return a.first.second > b.first.second;
    }
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    
    vector<pair<pair<int, int>, int>> tree; // <x, y>, num
    tree.resize(nodeinfo.size());
    

    for(int i = 0; i<nodeinfo.size(); i++){
        pair node = {nodeinfo[i][0], nodeinfo[i][1]};
        pair node_with_num = make_pair(node, i+1);
        tree[i] = node_with_num;
    }
    sort(tree.begin(), tree.end(), cmp);
    
    Treenode* root = new Treenode(tree[0].first.first,
                                  tree[0].first.second,
                                  tree[0].second);
    
    for(int i = 1; i < tree.size(); i++){
        Treenode* node = new Treenode(tree[i].first.first,
                                      tree[i].first.second,
                                      tree[i].second);
        MakeTree(root, node);
    }
    
    PrintTree(root);
    
    Preorder(root);
    Postorder(root);
    
    answer.push_back(pre_array);
    answer.push_back(post_array);
    
    return answer;
}