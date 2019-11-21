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

struct hero{
    long long p;
    long long s;
    hero(long long p, long long s):p(p), s(s){}
};

ostream& operator<<(ostream &c, const hero &h){
    return c << "Hero: " << h.p << " " << h.s << endl;
}

long long get_last_geq(const vector<hero> &h, long long start, long long end, long long target){
    if(end - start < 1){
        return -1;
    }
    if(end - start == 1){
        if(h[start].s >= target){
            return start;
        }else{
            return -1;
        }
    }
    long long mid = (end - start)/2 + start;
    if(h[mid].s >= target){
        return get_last_geq(h, mid, end, target);
    }else{
        return get_last_geq(h, start, mid, target);
    }
}

int main(){
    long long t;
    cin >> t;
    for(long long i = 0; i<t; i++){
        long long n, m;
        cin >> n;
        vector<long long> monst_pwr;
        for(long long j = 0; j<n; j++){
            long long pwr;
            cin >> pwr;
            monst_pwr.push_back(pwr);
        }
        cin >> m;
        long long p, s;
        vector<hero> heroes;
        for(long long j = 0; j<m; j++){
            cin >> p >> s;
            hero h(p, s);
            heroes.push_back(h);
        }
        // Sort heroes in non-inc order by endurance (and then power).
        sort(heroes.begin(), heroes.end(), [](hero a, hero b){
            return (a.s > b.s || (a.s==b.s && a.p > b.p));});
        /*for(auto iter = heroes.begin(); iter!=heroes.end(); iter++){
            cout << *iter;
        }*/
        vector<long long>max_pwr_min_end;
        long long max_pwr = 0;
        for(long long j = 0; j<heroes.size(); j++){
            if(heroes[j].p > max_pwr){
                max_pwr = heroes[j].p;
            }
            max_pwr_min_end.push_back(max_pwr);
        }
        /*for(auto iter = max_pwr_min_end.begin(); iter!=max_pwr_min_end.end(); iter++){
            cout << *iter << endl;
        }
        cout << endl;
        
        /*cout << get_last_geq(heroes, 0, heroes.size(), 0) << endl;
        cout << get_last_geq(heroes, 0, heroes.size(), 1) << endl;
        cout << get_last_geq(heroes, 0, heroes.size(), 2) << endl;
        cout << get_last_geq(heroes, 0, heroes.size(), 3) << endl;
        cout << get_last_geq(heroes, 0, heroes.size(), 4) << endl;*/
        
        long long last_ind = 0;
        long long days = 0;
        long long max_monster_pwr = 0;
        bool failed = false;
        for(long long j = 0; j<n; j++){
            if(monst_pwr[j] > max_monster_pwr){
                max_monster_pwr = monst_pwr[j];
            }
            long long min_end_ind = get_last_geq(heroes, 0, heroes.size(), j+1 - last_ind);
            //cout << "end_ind " << min_end_ind << endl;
            if(min_end_ind == -1){
                days++;
                //cout << "Days: " << days << endl;
                //cout << "j: " << j << endl;
                if(j == last_ind){
                    // we can't complete the challenge
                    days = -1;
                    failed = true;
                    j = n;
                    break;
                }else{
                    // start over at a new day
                    last_ind = j;
                    max_monster_pwr = 0;
                    j--;    // Reconsider this monster
                }
            }
            else{
                long long max_hero_pwr = max_pwr_min_end[min_end_ind];
                if(max_hero_pwr < max_monster_pwr){
                    days++;
                    //cout << "Days: " << days << endl;
                    //cout << "j: " << j << endl;
                    if(j == last_ind){
                        // we can't complete the challenge
                        days = -1;
                        failed = true;
                        j = n;
                        break;
                    }else{
                        // start over at a new day
                        last_ind = j;
                        max_monster_pwr = 0;
                        j--;    // Reconsider this monster
                    }
                }
            }
        }
        if(failed){
            cout << days << endl;
        }else{
            // +1 because takes one final day to defeat remaining monsters
            cout << days + 1 << endl;
        }
    }
    return 0;
}
