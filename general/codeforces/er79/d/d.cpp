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

#define m 998244353

using namespace std;

template <class T>
void print(T s, T e){
    for(auto iter = s; iter != e; iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

template <class T>
void print_d(T s, T e){
    for(auto iter = s; iter != e; iter++){
        cout << "(" << iter->first << "->" << iter->second << ") ";
    }
    cout << endl;
}

ll mod(ll a, ll b){
    return ((a%b) + b)%b;
}

ll gcd(ll a, ll b){
    while(b){ ll t = a%b; a = b; b = t; }
    return a;
}

ll extended_euclid(ll a, ll b, ll &x, ll &y){
    ll xx = y = 0;
    ll yy = x = 1;
    while(b){
        ll q = a/b;
        ll t = b; b = a%b; a = t;
        t = xx; xx = x - q*xx; x = t;
        t = yy; yy = y - q*yy; y = t;
    }
    return a;
}

ll mod_inverse(ll a, ll n){
    ll x, y;
    ll g = extended_euclid(a, n, x, y);
    if(g > 1) return -1;
    return mod(x, n);
}

int main(){
    long long n;
    cin >> n;
    unordered_map<ll, ll> kids_with_gift;
    unordered_map<ll, vector<ll>> gift_to_reciprocals;
    for(long long i = 0; i<n; i++){
        ll k;
        cin >> k;
        for(ll j = 0; j<k; j++){
            ll g;
            cin >> g;
            if(kids_with_gift.find(g) == kids_with_gift.end()){
                kids_with_gift[g] = 1;
            }else{
                kids_with_gift[g]++;
            }
            if(gift_to_reciprocals.find(g) == gift_to_reciprocals.end()){
                vector<ll> tmp;
                tmp.push_back(k);
                gift_to_reciprocals[g] = tmp;
            }else{
                gift_to_reciprocals[g].push_back(k);
            }
        }
        
    }
    
    return 0;
}
