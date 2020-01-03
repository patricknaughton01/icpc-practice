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

template <class T>
void print_d(T s, T e){
    for(auto iter = s; iter != e; iter++){
        cout << "(" << iter->first << "->" << iter->second << ") ";
    }
    cout << endl;
}

int main(){
    long long t;
    cin >> t;
    for(long long i = 0; i<t; i++){
        ll n, m;
        cin >> n >> m;
        vector<ll> a;
        unordered_map<ll, ll> a_ind;
        vector<ll> b;
        for(ll j = 0; j<n; j++){
            ll val;
            cin >> val;
            a.push_back(val);
            a_ind[val] = j;
        }
        vector<ll> fetch_a_inds;
        for(ll j = 0; j<m; j++){
            ll val;
            cin >> val;
            b.push_back(val);
            fetch_a_inds.push_back(a_ind[val]);
        }
        ll largest_ind_seen = -1;
        ll time = 0;
        //print_d(a_ind.begin(), a_ind.end());
        for(ll j = 0; j<m; j++){
            if(fetch_a_inds[j] > largest_ind_seen){
                // j is number of presents we've already 
                // removed from the stack
                time += 2*(fetch_a_inds[j] - j) + 1;
                largest_ind_seen = fetch_a_inds[j];
            }else{
                time++;
            }
        }
        cout << time << endl;
        
        
    }
    return 0;
}
