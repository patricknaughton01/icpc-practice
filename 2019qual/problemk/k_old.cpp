#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<char, int> starts;

template <typename T>
void print_vec(vector<T> vec){
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

template <typename T, typename S>
void print_umap(unordered_map<T, S> umap){
    for(auto iter = umap.begin(); iter != umap.end(); iter++){
        cout << iter->first << " -> " << iter->second << endl;
    }
    cout << endl;
}

int main(){
    char type, last;
    vector<char> schedule;
    unordered_map<int, int> after;
    cin >> type;
    last = type;
    schedule.push_back(type);
    int ind = 0;
    starts[type] = ind;
    while(cin >> type){
        if(type != last){
            last = type;
            schedule.push_back(type);
            ind++;
            if(starts.find(type) != starts.end()){
                after[starts[type]] = ind-starts[type]-1;
                starts[type] = ind;
            }else{
                starts[type] = ind;
            }
            cout << type << " ";
        }
    }
    for(auto iter = starts.begin(); iter != starts.end(); iter++){
        after[iter->second] = schedule.size() - starts[schedule[iter->second]] - 1;
    }
    /*for(int i = after.size(); i < schedule.size(); i++){
        after.push_back(schedule.size() - starts[schedule[i]] - 1);
    }*/
    print_umap(starts);
    print_vec(schedule);
    print_umap(after);
    int sum = 0;
    for(auto iter = after.begin(); iter != after.end(); iter++){
        sum += iter->second;
    }
    cout << sum << endl;
    return 0;
}
