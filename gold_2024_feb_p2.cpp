#include<bits/stdc++.h>
#define int long long

#define lazypodinv lazyinvpod
#define segmin seg_min

using namespace std;

const int N = 500010;

struct Segtree{
    int tree[4*N], lazyadd[4*N], lazypod[4*N], lazypodinv[4*N];
    int join(int a, int b){
        return a+b;
    }
    void unlazy(int node, int l, int r){
        tree[node] += lazyadd[node]*(r-l+1);
        tree[node] += lazypod[node]*((r-l+1)*(r-l+2))/2;
        tree[node] += lazyinvpod[node]*((r-l+1)*(r-l+2))/2;
        if(l != r){
            lazyadd[2*node] += lazyadd[node];
            lazypod[2*node] += lazypod[node];
            lazyadd[2*node+1] += lazyadd[node];
            lazypod[2*node+1] += lazypod[node];
            int mid = (l+r)/2;
            lazyadd[2*node+1] += lazypod[node]*(mid-l+1);
            lazyadd[2*node] += lazyinvpod[node]*(r-mid); 
            lazyinvpod[2*node] += lazypodinv[node];
            lazypodinv[2*node+1] += lazyinvpod[node];
        }
        lazyadd[node] = lazypod[node] = lazyinvpod[node] =  0;
    }
    void build(int node, int l, int r){
        tree[node] = lazypod[node] = lazyadd[node] = lazypodinv[node] = 0;
        if(l == r) return;
        int mid = (l+r)/2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        return;
    }
    void updateadd(int node, int l, int r, int tl, int tr, int val){
        unlazy(node, tl, tr);
        if(l > tr or tl > r) return;
        if(l <= tl and tr <= r){
            lazyadd[node] += val;
            unlazy(node, tl, tr);
            return;
        }
        int mid = (tl+tr)/2;
        updateadd(2*node, l, r, tl, mid, val);
        updateadd(2*node+1, l, r, mid+1, tr, val);
        tree[node] = join(tree[2*node], tree[2*node+1]);
    }
    void updatepod(int node, int l, int r, int tl, int tr, int val){
        unlazy(node, tl, tr);
        if(l > tr or tl > r) return;
        if(l <= tl and tr <= r){
            lazyadd[node] += (tl-l)*val;
            lazypod[node] += val;
            unlazy(node, tl, tr);
            return;
        }
        int mid = (tl+tr)/2;
        updatepod(2*node, l, r, tl, mid, val);
        updatepod(2*node+1, l, r, mid+1, tr, val);
        tree[node] = join(tree[2*node], tree[2*node+1]);
        return;
    }
    void updatepodinv(int node, int l, int r, int tl, int tr, int val){
        unlazy(node, tl, tr);
        if(l > tr or tl > r) return;
        if(l <= tl and tr <= r){
            lazyadd[node] += (r-tr)*val;
            lazypodinv[node] += val;
            unlazy(node, tl, tr);
            return;
        }
        int mid = (tl+tr)/2;
        updatepodinv(2*node, l, r, tl, mid, val);
        updatepodinv(2*node+1, l, r, mid+1, tr, val);
        tree[node] = join(tree[2*node], tree[2*node+1]);
    }
    int query(int node, int l, int r, int tl, int tr){
        unlazy(node, tl, tr);
        if(l > tr or tl > r) return 0;
        if(l <= tl and tr <= r) return tree[node];
        int mid = (tl+tr)/2;
        return join(query(2*node, l, r, tl, mid), query(2*node+1, l, r, mid+1, tr));
    }
} seg;

int v[N];
int lg[N];
int n;

const int LOGN = 20;

struct Segtree_min{
    int sparse[N][LOGN];
    void build(int node, int l, int r){
        for(int i = 1;i <= n;i++){
            sparse[i][0] = v[i];
        }
        for(int bit = 1;bit < LOGN;bit++){
            for(int i = 1;i <= n;i++)
                sparse[i][bit] = min(sparse[i][bit-1], sparse[min(n, (i+(1<<(bit-1))))][bit-1]);
        }
    }
    int query(int node, int l, int r, int tl, int tr){
        int t = lg[r-l+1];
        return min(sparse[l][t], sparse[r-(1<<t)+1][t]);
    }
} seg_min;

int p[N], q[N];
int minv[N];

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);
    lg[1] = 0;
    for(int i = 2;i < N;i++){
        lg[i] = lg[i/2]+1;
    }
    cin >> n;
    int mn = 1e9+1;
    int posmn = 0;
    vector <int> vv;
    for(int i = 1;i <= n;i++){
        int x;
        cin >> x;
        vv.push_back(x);
        if(mn > x){
            posmn = i-1;
            mn = x;
        }
    }
    for(int i = 1;i <= n;i++){
        v[i] = vv[(i-1+posmn)%n];
    }
    seg.build(1, 1, n);
    segmin.build(1,1,n);
    for(int i = 1;i <= n;i++){
        int l = i, r = n;
        if(segmin.query(1, i, n, 1, n) == v[i]){
            p[i] = n-i;
            continue;
        }
        int ans = 0;
        while(l <= r){
            int mid = (l+r)/2;
            int qr = segmin.query(1, i, mid, 1,n);
            if(qr < v[i]){
                r = mid-1;
                ans = mid;
            }
            else{
                l = mid+1;
            }
        }
        p[i] = ans-i-1;
    }
    for(int i = 2;i <= n;i++){
        int l = 1, r = i-1;
        int ans = 0;
        while(l <= r){
            int mid = (l+r)/2;
            int qr = segmin.query(1, mid, i-1, 1, n);
            if(qr <= v[i]){
                l = mid+1;
                ans = mid;
            }
            else{
                r = mid-1;
            }
        }
        q[i] = i-ans;
    }
    for(int i = 2;i <= n;i++){
        if(p[i] >= q[i]){
            if(q[i]-1 > 0) {
                seg.updatepod(1, 1, q[i]-1, 1, n, v[i]);
                seg.updateadd(1, 1, q[i]-1, 1, n, v[i]);
            }
            seg.updateadd(1, q[i], p[i], 1, n, v[i]*q[i]);
            if(q[i] > 1) seg.updatepodinv(1, p[i]+1, p[i]+q[i]-1, 1, n, v[i]);
        }
        else{
            if(p[i] > 1){
                seg.updatepod(1, 1, p[i]-1, 1, n, v[i]);
                seg.updateadd(1, 1, p[i]-1, 1, n, v[i]);
            }
            seg.updateadd(1, max(1LL, p[i]), q[i]-1, 1, n, v[i]*(p[i]+1));
            if(p[i] >= 1){
                seg.updatepodinv(1, q[i], q[i]+p[i]-1, 1, n, v[i]);
            }
        }
    }
    for(int i = 1;i <= n;i++){
        cout << seg.query(1, i, i, 1, n)+v[1]*min(n, (i+1)) << '\n';
    }
    return 0;
}
