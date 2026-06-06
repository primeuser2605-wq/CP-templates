struct Node{
    int mn;
    int cnt;
};

class SegmentTree{
private:
    vector<Node> tree;
    vector<int> arr;
    int n;

    Node merge(const Node &a,const Node &b){
        if(a.mn<b.mn) return a;
        if(b.mn<a.mn) return b;
        return {a.mn,a.cnt+b.cnt};
    }

    void build(int idx,int l,int r){
        if(l==r){
            tree[idx]={arr[l],1};
            return;
        }

        int mid=(l+r)/2;

        build(2*idx+1,l,mid);
        build(2*idx+2,mid+1,r);

        tree[idx]=merge(tree[2*idx+1],tree[2*idx+2]);
    }

    Node query(int idx,int l,int r,int ql,int qr){
        if(ql>r||qr<l) return {INT_MAX,0};

        if(ql<=l&&r<=qr) return tree[idx];

        int mid=(l+r)/2;

        Node leftRes=query(2*idx+1,l,mid,ql,qr);
        Node rightRes=query(2*idx+2,mid+1,r,ql,qr);

        return merge(leftRes,rightRes);
    }

    void update(int idx,int l,int r,int pos,int val){
        if(l==r){
            arr[l]=val;
            tree[idx]={val,1};
            return;
        }

        int mid=(l+r)/2;

        if(pos<=mid) update(2*idx+1,l,mid,pos,val);
        else update(2*idx+2,mid+1,r,pos,val);

        tree[idx]=merge(tree[2*idx+1],tree[2*idx+2]);
    }

public:
    SegmentTree(const vector<int>& input){
        arr=input;
        n=arr.size();

        tree.resize(4*n);

        build(0,0,n-1);
    }

    Node getMin(int l,int r){
        return query(0,0,n-1,l,r);
    }

    void setValue(int pos,int val){
        update(0,0,n-1,pos,val);
    }
};
