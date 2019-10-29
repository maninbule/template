模板题链接：https://www.luogu.org/problem/P3366

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 2e5+10;
struct ed{
    int a,b,w;
    bool operator <(const ed &o)const{ //按照边权从小到大排序
        return w<o.w;
    }
};
vector<ed> edges;
int fa[maxn];
int N,M;
long long res = 0,coun = 0;
int find(int x){ 
    return x == fa[x]? x:fa[x] = find(fa[x]);
}
void join(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx!=fy) fa[fx] = fy;
}

int main(){
    cin>>N>>M;
    for(int i = 0;i<N;i++) fa[i] = i;
    int a,b,w;
    for(int i = 0;i<M;i++){
        scanf("%d%d%d",&a,&b,&w);
        edges.push_back({a,b,w});
    }
    sort(edges.begin(),edges.end());
    for(int i = 0;i<M;i++){
        int a = edges[i].a,b = edges[i].b,w = edges[i].w;
        if(find(a) != find(b)){
            join(a,b);
            res += w;//加和构图时用的边权
            coun++;//记录边的数量
        }
    }
    if(coun!=N-1) cout<<"orz"<<endl;//没有构成树的条件
    else cout<<res<<endl;

    return 0;
}
