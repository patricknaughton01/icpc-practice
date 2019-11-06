#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

template<class T>
void print_vec(vector<T> vec);
template<class T, class U>
void print_map(unordered_map<T, U> map);

int main(){
    int n, m;
    cin >> n;
    cin >> m;
    vector<long> starts;
    vector<long> ends;
    long tmp;
    for(int i = 0; i<n; i++){
        cin >> tmp;
        starts.push_back(tmp);
    }
    for(int i = 0; i<m; i++){
        cin >> tmp;
        ends.push_back(tmp);
    }
    //print_vec(starts);
    //print_vec(ends);
    int highestOccurence = 0;
    int time = 0;
    unordered_map<long, int> occurences;
    for(int i = 0, n = starts.size(); i<n; i++){
        for(int j = 0, m = ends.size(); j<m; j++){
            long diff = ends[j] - starts[i];
            if(diff >= 0){
                if(occurences.find(diff) == occurences.end()){ // not in the map
                    occurences[diff] = 1;
                }else{
                    occurences[diff] += 1;
                }
                //cout << diff << endl;
                if(occurences[diff] > highestOccurence){
                    highestOccurence = occurences[diff];
                    time = diff;
                }else if(occurences[diff] == highestOccurence && diff < time){
                    time = diff;
                }
            }
        }
    }
    cout << time << endl;
    //print_map(occurences);
    return 0;
}

template<class T>
void print_vec(vector<T> vec){
    for(long i = 0; i<vec.size(); i++){
        cout << vec[i] << " ";
    }
    cout << endl;
}

template<class T, class U>
void print_map(unordered_map<T, U> map){
    for(auto& x:map){
        cout << x.first << ":" << x.second << " ";
    }
    cout << endl;
}
