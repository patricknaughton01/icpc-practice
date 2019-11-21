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
    int t;
    cin >> t;
    for(int i = 0; i<t; i++){
        int n, x, a, b;
        cin >> n >> x >> a >> b;
        cout << MIN(ABS(b-a)+x, n-1) << endl;
    }
    return 0;
}
