#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 200010;
int l[N], r[N];
int p[N], s[N];
int res[N];
int val[N];

void solve(){
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> p[i];
    }
    for(int i = 1;i <= n;i++){
        cin >> s[i];
    }
    for(int i = 1;i <= n;i++){
        r[i] = i+1;
        l[i] = i-1;
    }
    set <array <int, 3>> st;
    for(int i = 1;i < n;i++){
        if(i%2 == 1){
            int dif = p[i+1]-p[i];
            int sum = s[i+1]+s[i];
            int k = (dif+sum-1)/sum;
            st.insert({2*k-1, i,i+1});
            val[i] = 2*k-1;
        }
        else{
            int dif = p[i+1]-p[i];
            int sum = s[i+1]+s[i];
            int k = (dif+sum-1)/sum;
            st.insert({2*k, i,i+1});    
            val[i] = 2*k;
        }
    }
    while(!st.empty()){
        auto [k, x, y] = (*st.begin());
        st.erase({k, x, y});
        int a = l[x], b = r[y];
        r[a] = b;
        l[b] = a;
        res[x] = k;
        res[y] = k;
        if(a != 0){
            st.erase({val[a], a, x});
        }
        if(b != n+1){
            st.erase({val[y], y, b});
        }
        if(a == 0 or b == n+1) continue;
        int dif = p[b]-p[a];
        int sum = s[a]+s[b];
        k = (dif+sum-1)/sum;
        if(a%2 == 1){
            val[a] = 2*k-1;
            st.insert({val[a], a, b});
        }
        else{
            val[a] = 2*k;
            st.insert({val[a], a, b});
        }
    }
    for(int i = 1;i < n;i++){
        cout << res[i] << ' ';
    }
    cout << res[n] << '\n';
}

int32_t main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
