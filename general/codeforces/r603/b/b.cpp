#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))

using namespace std;

int main(){
    int t;
    cin >> t;
    for(int i = 0; i<t; i++){
        int n;
        cin >> n;
        vector<string> codes;
        unordered_map<string, int> freq;
        unordered_set<int> free_first_nums;
        for(int j = 0; j<10; j++){
            free_first_nums.insert(j);
        }
        for(int i = 0; i<n; i++){
            string c;
            cin >> c;
            codes.push_back(c);
            if(freq.find(c) == freq.end()){
                freq[c] = 1;
            }else{
                freq[c]++;
            }
            int fn = c[0] - '0';
            free_first_nums.erase(fn);
        }
        int changes = codes.size() - freq.size();
        cout << changes << endl;
        if(changes == 0){
            for(int j = 0; j<codes.size(); j++){
                cout << codes[j] << endl;
            }
        }else{
            for(int j = 0; j<codes.size(); j++){
                if(freq[codes[j]] == 1){
                    cout << codes[j] << endl;
                }else{
                    freq[codes[j]]--;
                    int new_first = *(free_first_nums.begin());
                    free_first_nums.erase(new_first);
                    codes[j][0] = new_first + '0';
                    cout << codes[j] << endl;
                }
            }
        }
    }
    return 0;
}
