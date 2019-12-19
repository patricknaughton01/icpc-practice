#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>

#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))

using namespace std;

template<typename T>
void print_set(set<T> s){
    for(auto iter = s.begin(); iter!=s.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

int main(){
    long long n;
    cin >> n;
    long long ind;
    string commands;
    cin >> commands;
    set<long long> opens;
    set<long long> closes;
    for(long long i = 0; i<n; i++){
        if(commands[i] == 'R'){
            ind++;
        }else if(commands[i] == 'L'){
            ind = MAX(ind-1, 0);
        }
        else if(commands[i] == '('){
            opens.insert(ind);
        }else if(commands[i] == ')'){
            closes.insert(ind);
        }else{
            opens.erase(ind);
            closes.erase(ind);
        }
        if(opens.size() != closes.size()){
            cout << -1 << " ";
        }else{
            long long max_depth = 0;
            long long depth = 0;
            auto open_iter = opens.begin();
            auto close_iter = closes.begin();
            /*cout << "Opens: ";
            print_set(opens);
            cout << "Closes: ";
            print_set(closes);*/
            while(open_iter != opens.end() || close_iter != closes.end()){
                if(open_iter == opens.end() || *close_iter < *open_iter){
                    if(depth == 0){
                        cout << -1 << " ";
                        break;
                    }else{
                        depth--;
                        close_iter++;
                    }
                }else{
                    depth++;
                    max_depth = MAX(depth, max_depth);
                    open_iter++;
                }
            }
            if(close_iter != closes.end()){
                cout << -1 << " ";
            }else{
                cout << max_depth << " ";
            }
        }
    }
    cout << endl;
    return 0;    
}
