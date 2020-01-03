#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>

#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))
#define ABS(x) ((x)>0?(x):(-(x)))
#define ll long long

using namespace std;

template <class T>
void print(T s, T e){
    for(auto iter = s; iter != e; iter++){
        cout << *iter << " ";
    }
    cout << endl;
}


int main(){
    long long k1, k2, k3;
    cin >> k1 >> k2 >> k3;
    ll n = k1 + k2 + k3;
    unordered_map<ll, int> start;
    for(ll i = 0; i<k1; i++){
        ll val;
        cin >> val;
        start[val] = 0;
    }
    for(ll i = 0; i<k2; i++){
        ll val;
        cin >> val;
        start[val] = 1;
    }
    for(ll i = 0; i<k3; i++){
        ll val;
        cin >> val;
        start[val] = 2;
    }
    vector<vector<ll>> dp;
    for(ll i = 0; i <= n; i++){
        vector<ll> tmp(3, 0);
        dp.push_back(tmp);
    }
    for(ll i = 1; i<=n; i++){
        int cost[3] = {!(start[i]==0), !(start[i]==1), !(start[i]==2)};
        dp[i][0] = dp[i-1][0] + cost[0];
        dp[i][1] = MIN(dp[i-1][1], dp[i-1][0]) + cost[1];
        dp[i][2] = MIN(MIN(dp[i-1][0], dp[i-1][1]), dp[i-1][2]) + cost[2];
    }
    /*for(ll i = 0; i<dp.size(); i++){
        print(dp[i].begin(), dp[i].end());
    }*/
    cout << MIN(MIN(dp[n][0], dp[n][1]), dp[n][2]) << endl;
    return 0;
}
