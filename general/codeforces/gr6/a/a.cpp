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
    //vector<int> nonzeroes;
    int n;
    cin >> n;
    for(int i = 0; i<n; i++){
        string s;
        cin >> s;
        int numzeroes = 0;
        bool seen_even = false;
        int total = 0;
        for(int j = 0; j<s.size(); j++){
            if(s[j] == '0'){
                numzeroes++;
            }else{
                int val = (s[j] - '0');
                if(val%2 == 0){
                    seen_even = true;
                }
                total += val;
            }
        }
        //cout << "Zereos: " << numzeroes << endl;
        //cout << "Total: " << total << endl;
        if((total%3==0 && (numzeroes>=1 && seen_even)) || (total%3==0 && (numzeroes>=2))){
            cout << "red" << endl;
        }else{
            cout << "cyan" << endl;
        }
    }
    return 0;
}
