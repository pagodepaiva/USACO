#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 50010;
const int inf = 1e13;
array <pair <int, int>, 14> dist[N];
int n, m, c, r, k;
vector <pair <int, int>> g[N];

int32_t main(){ 
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> c >> r >> k;
    for(int i = 1;i <= m;i++){
        int a, b, w;
        cin >> a >> b >> w;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }
    priority_queue <array <int, 4>> pq;
    for(int i = 1;i <= n;i++){
        for(int j = 0;j < k;j++){
            dist[i][j] = {inf, inf};
        }
    }
    for(int i = 1;i <= c;i++){
        dist[i][0] = {0, i};
        pq.push({0, i, i, 0});
    }
    while(!pq.empty()){
        auto [d, start, v, pos] = pq.top();
        pq.pop();
        d *= -1;
        if(make_pair(d, start) != dist[v][pos]) continue;
        for(auto [x, w] : g[v]){
            for(int i = 0;i < k;i++){
                if(dist[x][i].first > d+w){
                    int l = k;
                    for(int j = 0;j < k;j++){
                        if(dist[x][j].second == start){
                            l = j;
                            break;
                        }
                    }
                    for(int j = l-1;j >= i;j--){
                        if(j+1 < k) {
                            dist[x][j+1] = dist[x][j];
                            pq.push({-dist[x][j+1].first, dist[x][j+1].second, x, j+1});
                        }
                    }
                    dist[x][i] = {d+w, start};
                    pq.push({-dist[x][i].first, dist[x][i].second, x, i}); 
                    break;
                }
                if(dist[x][i].second == start) break;
            }
        }
    }
    vector <int> ans;
    for(int i = c+1;i <= n;i++){
        if(dist[i][k-1].first <= r) ans.push_back(i);
        //cout << dist[i][k-1].first << ' ';
    }
    if(ans.empty()){
        cout << 0 << '\n';
        return 0;
    }
    cout << ans.size() << '\n';
    for(auto x : ans){
        cout << x << '\n';
    }
}
