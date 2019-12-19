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

template <class T>
void print_d(T s, T e){
    for(auto iter = s; iter != e; iter++){
        cout << "(" << iter->first << "->" << iter->second << ") ";
    }
    cout << endl;
}

long long get_n(long long min, long long max, long long targ){
    if(max - min <= 0){
        return min;
    }
    long long mid = (max-min)/2 + min;
    long long val = (mid*(mid+1))/2;
    if(val >= targ){
        return get_n(min, mid, targ);
    }else{
        return get_n(mid+1, max, targ);
    }
}

long long tri(long long n){
    return (n*(n+1))/2;
}

int main(){
    int t;
    /*for(long long j = 0; j<100; j++){
        cout << "j: " << j << " n: " << get_n(1, j, j) << endl;
    }*/
    cin >> t;
    for(int i = 0; i<t; i++){
        long long a, b;
        cin >> a >> b;
        if(a == b){
            cout << 0 << endl;
            continue;
        }
        long long s = MIN(a, b), t = MAX(a, b);
        long long diff = t-s;
        // Get index of first triangle num that is at least diff
        long long n = get_n(1, diff, diff);
        if(diff%2 == 0){
            while(tri(n)%2 != 0){n++;}
            cout << n << endl;
        }else{
            while(tri(n)%2 != 1){n++;}
            cout << n << endl;
        }
    }
    return 0;
}
