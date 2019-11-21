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
#define ABS(x) ((x)<0?(-(x)):(x))

using namespace std;

int main(){
    long long t;
    cin >> t;
    for(long long i = 0; i<t; i++){
        long long x, y;
        cin >> x >> y;
        if(x>=y){
            // can just keep subtracting one
            cout << "YES" << endl;
            continue;
        }else if(x==1 && y > 1){
            // Can't use any spells
            cout << "NO" << endl;
            continue;
        }else{
            long long tmp = x;
            if(tmp%2==1){
                tmp-=1;
            }
            tmp /= 2;
            tmp *= 3;
            if(tmp == y){
                cout << "YES" << endl;
            }else if((tmp>x && tmp%2==0) || (tmp%2==1 && tmp-1>x)){
                cout << "YES" << endl;
            }else{
                cout << "NO" << endl;
            }
            continue;
        }
    }
    return 0;
}
