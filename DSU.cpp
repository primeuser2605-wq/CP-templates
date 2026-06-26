#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class DSU {
public:
    vector<int> par, rnk, sz;
    int comp, mx;

    DSU(int n) {
        par.resize(n + 1);
        rnk.assign(n + 1, 0);
        sz.assign(n + 1, 1);

        comp = n;
        mx = 1;

        for (int i = 1; i <= n; i++)
            par[i] = i;
    }

    int find(int x) {
        if (par[x] != x)
            par[x] = find(par[x]);
        return par[x];
    }

    bool merge(int x, int y) {
        int lx = find(x);
        int ly = find(y);

        if (lx == ly)
            return false;

        if (rnk[lx] > rnk[ly]) {
            par[ly] = lx;
            sz[lx] += sz[ly];
            mx = max(mx, sz[lx]);
        }
        else if (rnk[lx] < rnk[ly]) {
            par[lx] = ly;
            sz[ly] += sz[lx];
            mx = max(mx, sz[ly]);
        }
        else {
            par[lx] = ly;
            rnk[ly]++;
            sz[ly] += sz[lx];
            mx = max(mx, sz[ly]);
        }

        comp--;
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }

    int components() {
        return comp;
    }

    int maxSize() {
        return mx;
    }
};



class UnionFind {
private:
    vector<int> p, rank;

public:
    UnionFind(int n) {
        rank.assign(n, 0);
        p.assign(n, 0);
        iota(p.begin(), p.end(), 0); // each node is its own parent initially
    }

    int findSet(int i) {
        return (p[i] == i) ? i : (p[i] = findSet(p[i]));
    }

    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y])
                p[y] = x;
            else {
                p[x] = y;
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }
    }
};

// DSU by height
vector<int> root, sz;

int par(int x){
    if(x==root[x]) return x;
    
    return root[x]=par(root[x]);
}

bool join(int a, int b){
    a=par(a);
    b=par(b);
    if(a==b) return false;
    
    if(sz[a]>sz[b]) swap(a,b);
    
    root[a]=b;
    sz[b]+=sz[a];
    return true;
}
