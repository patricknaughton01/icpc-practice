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

using namespace std;

template <class T>
void print(T s, T e){
    for(auto iter = s; iter != e; iter++){
        cout << *iter << " ";
    }
    cout << endl;
}


int main(){
    int t;
    cin >> t;
    for(int i = 0; i<t; i++){
        long long n;
        cin >> n;
        unordered_map<long long, long long> num_to_ind;
        for(long long j = 0; j<n; j++){
            long long val;
            cin >> val;
            num_to_ind[val] = j;
        }
        set<long long> inds;
        string beautifuls;
        for(long long j = 0; j<n; j++){
            inds.insert(num_to_ind[j+1]);
            long long first = *(inds.begin());
            long long last = *(inds.rbegin());
            if(last - first == j){
                beautifuls += '1';
            }else{
                beautifuls += '0';
            }
        }
        cout << beautifuls << endl;
    }
    return 0;
}
