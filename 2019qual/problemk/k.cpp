#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

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
    //unordered_map<int, int> after;
    cin >> type;
    last = type;
    schedule.push_back(type);
    while(cin >> type){
        if(type != last){
            last = type;
            schedule.push_back(type);
        }
    }
    //print_vec(schedule);
    int sum = 0;
    for(int i = 0; i<schedule.size()-1; i++){
        unordered_set<char> seen;
        for(int j = i+1; j < schedule.size(); j++){
            if(schedule[j] != schedule[i] && seen.find(schedule[j]) == seen.end()){
                sum++;
                seen.insert(schedule[j]);
            }else if(schedule[j] == schedule[i]){
                break;
            }
        }
    }
    cout << sum << endl;
    return 0;
}
