#include <bits/stdc++.h>
using namespace std;
 
const int MAXN=200005;
const int MAX_BITS=20;

vector<int> adj[MAXN];
int up[MAXN][MAX_BITS];
int depth[MAXN];

void dfs(int u,int p,int d){
    depth[u]=d;
    up[u][0]=p;

    for(int i=1;i<MAX_BITS;i++){
        up[u][i]=up[up[u][i-1]][i-1];
    }

    for(int v:adj[u]){
        if(v!=p){
            dfs(v,u,d+1);
        }
    }
}

int get_kth_ancestor(int u,int k){
    for(int i=0;i<MAX_BITS;i++){
        if((k>>i)&1){
            u=up[u][i];
        }
    }
    return u;
}

bool is_ancestor(int u,int v){
    if(depth[u]>depth[v]) return false;

    int diff=depth[v]-depth[u];
    return get_kth_ancestor(v,diff)==u;
}

int get_lca(int u,int v){
    if(depth[u]<depth[v]) swap(u,v);

    u=get_kth_ancestor(u,depth[u]-depth[v]);

    if(u==v) return u;

    for(int i=MAX_BITS-1;i>=0;i--){
        if(up[u][i]!=up[v][i]){
            u=up[u][i];
            v=up[v][i];
        }
    }

    return up[u][0];
}
