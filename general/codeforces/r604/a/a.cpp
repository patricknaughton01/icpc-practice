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
        string s;
        cin >> s;
        // check if given string is beautiful
        bool beautiful = true;
        for(int j = 0; j<s.size()-1; j++){
            if(s[j] == s[j+1] && s[j] != '?'){
                cout << -1 << endl;
                beautiful = false;
                break;
            }
        }
        if(beautiful){
            // each ? only has two neighbors so we can def make it beautiful
            unordered_set<char> allowed;
            for(int j = 1; j<s.size()-1; j++){
                if(s[j] == '?'){
                    allowed.insert('a');
                    allowed.insert('b');
                    allowed.insert('c');
                    allowed.erase(s[j-1]);
                    allowed.erase(s[j+1]);
                    s[j] = *(allowed.begin());
                }
            }
            if(s[0] == '?'){
                allowed.insert('a');
                allowed.insert('b');
                allowed.insert('c');
                if(s.size() > 1){
                    allowed.erase(s[1]);
                }
                s[0] = *(allowed.begin());
            }
            if(s[s.size()-1] == '?'){
                allowed.insert('a');
                allowed.insert('b');
                allowed.insert('c');
                if(s.size() > 1){
                    allowed.erase(s[s.size()-2]);
                    s[s.size()-1] = *(allowed.begin());
                }
            }
            cout << s << endl;
        }
    }
    return 0;
}
