class SGTree{
    vector<int>seg,lazy;
    public:
    SGTree(int n){
        seg.resize(4*n);
        lazy.resize(4*n,0);
    }
    void build(int ind,int low,int high,int arr[]){
        if(low==high)
        {
            seg[ind]=arr[low];
            return;
        }
        int mid = (low+high)>>1;
        build(2*ind+1,low,mid,arr);
        build(2*ind+2,mid+1,high,arr);
        seg[ind] = seg[2*ind+1]+seg[2*ind+2];
    }
    void update(int ind,int low,int high,int l,int r,int val)
    {
        //Update the previous remaining updates & propagate downwords
        if(lazy[ind]!=0){
            seg[ind] = (high-low+1)*lazy[ind];
            //Propagate the lazy update downwords for the remaining child nodes
            if(low!=high)
            {
                lazy[2*ind+1]=lazy[ind];
                lazy[2*ind+2]=lazy[ind];
            }
            lazy[ind]=0;
        }

        //No Overlap
        //low high l r Or l r low high
        if(high<l || r<low){
            return;
        }
        //Complete overlap  l low high r
        if(low>=l && high<=r){
            seg[ind]+=(high-low+1)*val;
            if(low!=high)
            {
                lazy[2*ind+1]+=val;
                lazy[2*ind+2]+=val;
            }
            return;
        }
        //Partial Overlap
        int mid = (low+high)>>1;
        update(2*ind+1,low,mid,l,r,val);
        update(2*ind+2,mid+1,high,l,r,val);
        seg[ind] = seg[2*ind+1]+seg[2*ind+2];
    }

    int querys(int ind,int low,int high,int l,int r){
        //Update if and update remaining as the node will stay fresh
        if(lazy[ind]!=0)
        {
            seg[ind]+=(high-low+1)*lazy[ind];
            if(low!=high)
            {
                lazy[2*ind+1]+=lazy[ind];
                lazy[2*ind+2]+=lazy[ind];
            }
            lazy[ind]=0;
        }

        // No Overlap
        if(high<l || r<low)
            return 0;
        // Complete overlap
        if(low>=l && high<=r)
            return seg[ind];
        
        //partial Overlape
        int mid = (low+high)>>1;
        int left = querys(2*ind+1,low,mid,l,r);
        int right = querys(2*ind+2,mid+1,high,l,r);
        return left+right;
    }
};
