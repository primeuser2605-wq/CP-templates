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
