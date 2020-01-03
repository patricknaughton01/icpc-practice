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

int main(){
    long long t;
    cin >> t;
    for(long long i = 0; i<t; i++){
        long long a, b, c, r, tmp0, tmp1;
        cin >> tmp0 >> tmp1 >> c >> r;
        a = MIN(tmp0, tmp1);
        b = MAX(tmp0, tmp1);
        long long c0 = c-r, c1 = c+r;
        if(a >= c1 || b <= c0){
            cout << b-a << endl;
        }else if(a < c1 && a >= c0){
            cout << MAX(b-a - (c1-a), 0) << endl;
        }else if (a <= c0 && c1 <= b){
            cout << b-a - (c1-c0) << endl;
        }else if(c0 < b && c1 >= b){
            cout << MAX(b-a - (b-c0), 0) << endl;
        }
    }
    return 0;
}
