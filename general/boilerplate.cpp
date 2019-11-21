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

using namespace std;

template <typename S, T>
void print(S<T> c){
    for(auto iter = c.begin(); iter != c.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}


int main(){
    vector<int> x(10, 0);
    print(x);
    return 0;
}
