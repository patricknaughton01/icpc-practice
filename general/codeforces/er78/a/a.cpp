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
    int t;
    cin >> t;
    for(int i = 0; i<t; i++){
        string p, h;
        cin >> p >> h;
        unordered_map<char, int> p_letters;
        for(int j = 0; j<p.size(); j++){
            if(p_letters.find(p[j])==p_letters.end()){
                p_letters[p[j]] = 1;
            }else{
                p_letters[p[j]]++;
            }
        }
        //print_d(p_letters.begin(), p_letters.end());
        bool test_true = false;
        for(int j = 0; j<=(int)h.size() - (int)p.size(); j++){
            //cout << "J: " << j << endl;
            unordered_map<char, int>test = p_letters;
            bool valid = true;
            //print_d(test.begin(), test.end());
            for(int k = j; k<j+p.size(); k++){
                if(test.find(h[k]) == test.end()){
                    valid = false;
                    break;
                }else if(test[h[k]] == 0){
                    valid = false;
                    break;
                }else{
                    test[h[k]]--;
                }
            }
            //cout << "Valid 1: " << valid << endl;
            if(valid){
                for(auto iter = test.begin(); iter!=test.end(); iter++){
                    if(iter->second != 0){
                        valid = false;
                    }
                }
            }
            //cout << "Valid 2: " << valid << endl;
            if(valid){
                cout << "YES" << endl;
                test_true = true;
                break;
            }
        }
        if(!test_true){
            cout << "NO" << endl;    
        }
    }
    return 0;
}
