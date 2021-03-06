#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct seg{int s, e, x, y;};

vector<seg> sweep;
vector<int> px;

struct segtree{
    int tree[2100000], lazy[2100000];
    void lazydown(int p){
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
        tree[2*p] += lazy[p];
        tree[2*p+1] += lazy[p];
        lazy[p] = 0;
    }
    void add(int s, int e, int ps, int pe, int p, int v){
        if(e < ps || pe < s) return;
        if(s <= ps && pe <= e){
            tree[p] += v;
            lazy[p] += v;
            return;
        }
        lazydown(p);
        int pm = (ps + pe) / 2;
        add(s, e, ps, pm, 2*p, v);
        add(s, e, pm+1, pe, 2*p+1, v);
        tree[p] = max(tree[2*p], tree[2*p+1]);
    }
}tree;

void solve(){
    int m;
    scanf("%d",&m);
    sweep.clear();
    px.clear();
    while(m--){
        int q;
        pi a[105];
        scanf("%d",&q);
        for(int i=0; i<q; i++){
            scanf("%d %d",&a[i].first, &a[i].second);
        }
        a[q] = a[0];
        for(int i=0; i<q; i++){
            if(a[i].first < a[i+1].first){
                sweep.push_back({a[i].first, a[i+1].first, a[i].second, -1});
            }
            else if(a[i].first > a[i+1].first){
                sweep.push_back({a[i+1].first, a[i].first, a[i].second, +1});
            }
        }
    }
    for(auto &i : sweep){
        px.push_back(i.s);
        px.push_back(i.e);
    }
    sort(px.begin(), px.end());
    px.resize(unique(px.begin(), px.end()) - px.begin());
    for(auto &i : sweep){
        i.s = lower_bound(px.begin(), px.end(), i.s) - px.begin();
        i.e = lower_bound(px.begin(), px.end(), i.e) - px.begin();
    }
    sort(sweep.begin(), sweep.end(), [&](const seg &a, const seg &b){
        return a.x > b.x;
    });
    int e = 0;
    int ret = 0;
    for(int i=0; i<sweep.size(); ){
        while(e < sweep.size() && sweep[e].x == sweep[i].x) e++;
        for(int j=i; j<e; j++){
            tree.add(sweep[j].s, sweep[j].e - 1, 0, px.size()-1, 1, sweep[j].y);
        }
        ret = max(ret, tree.tree[1]);
        i = e;
    }
    cout << ret << endl;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}