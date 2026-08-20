class DSU {
public:
    vector<int> par,rnk,sz;
    int comp,mx;

    struct Change {
        int lx,ly;
        int rankLy,sizeLy;
        int oldMx;
    };

    vector<Change> history;

    DSU(int n) {
        par.resize(n+1);
        rnk.assign(n+1,0);
        sz.assign(n+1,1);

        comp=n;
        mx=1;

        for(int i=0;i<=n;i++)
            par[i]=i;
    }

    int find(int x) {
        if(par[x]!=x)
            return find(par[x]);
        return par[x];
    }

    bool merge(int x,int y) {
        int lx=find(x);
        int ly=find(y);

        if(lx==ly)
            return false;

        if(rnk[lx]>rnk[ly])
            swap(lx,ly);

        history.push_back({lx,ly,rnk[ly],sz[ly],mx});

        par[lx]=ly;
        sz[ly]+=sz[lx];

        if(rnk[lx]==rnk[ly])
            rnk[ly]++;

        mx=max(mx,sz[ly]);
        comp--;

        return true;
    }

    void rollback() {
        if(history.empty())
            return;

        Change c=history.back();
        history.pop_back();

        par[c.lx]=c.lx;
        rnk[c.ly]=c.rankLy;
        sz[c.ly]=c.sizeLy;

        mx=c.oldMx;
        comp++;
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
