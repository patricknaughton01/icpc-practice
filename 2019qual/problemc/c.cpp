#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

#define ABS(x) ((x)>0? (x):-(x))

using namespace std;

map<int, vector<int>> districts;

int main(){
    int p, d;
    cin >> p >> d;
    int d_val, a_votes, b_votes;
    for(int i = 0; i<p; i++){
        cin >> d_val >> a_votes >> b_votes;
        if(districts.find(d_val) == districts.end()){
            vector<int> votes;
            votes.push_back(a_votes);
            votes.push_back(b_votes);
            districts[d_val] = votes;
        }else{
            districts[d_val][0] += a_votes;
            districts[d_val][1] += b_votes;
        }
    }
    /*for(auto iter = districts.begin(); iter != districts.end(); iter++){
        cout << iter->first << " " << iter->second[0] << " " << iter->second[1] << endl;
    }*/
    int wa = 0;
    int wb = 0;
    int total_v = 0;
    for(auto iter = districts.begin(); iter != districts.end(); iter++){
        vector<int> v = iter->second;
        int twa, twb;
        total_v += v[0];
        total_v += v[1];
        if(v[0] > v[1]){
            cout << "A ";
            twa = v[0] - ((v[0] + v[1])/2 + 1);
            twb = v[1];
            cout << twa << " " << twb << endl;
        }else{
            twb = v[1] - ((v[0] + v[1])/2 + 1);
            twa = v[0];
            cout << "B " << twa << " " << twb << endl;
        }
        wa += twa;
        wb += twb;
    }
    cout << (double)ABS(wa-wb)/(double)total_v << endl;
    return 0;
}
