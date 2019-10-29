#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
using namespace std;
const int maxn = 1e4+10;
struct ed{
    int v,w;
};
int d;//直径结果
int N,W;
vector<ed> adj[maxn];
int DFS(int u = 1,int fa = -1){
    int h1 = 0,h2 = 0;
    for(auto node:adj[u]){
        if(node.v == fa) continue;
        int h = DFS(node.v,u)+node.w;
        if(h>h1) h2 = h1,h1 = h; //记录最长和次长
        else if(h>h2) h2 = h;
    }
    d = max(d,h1+h2);
    return h1;
}
int main(){
    cin>>N>>W;
    int a,b,w;char cc;
    for(int i = 1;i<=W;i++){
        scanf("%d%d%d",&a,&b,&w); //两个端点以及权值
        adj[a].push_back({b,w});
        adj[b].push_back({a,w});
    }
    DFS(1,-1);
    cout<<d<<endl;
    return 0;
}
