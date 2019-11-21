#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define INFTY 1000000000000000000
#define MINLEN 3
#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))

using namespace std;

template <typename T>
void print_vec(vector<T> vec){
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

template <typename T>
void print_set(set<T> set){
    for(auto iter = set.begin(); iter != set.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

struct student{
    long long skill;
    long long index;
    long long team;
    
    student(long long s, long long i):skill(s), index(i), team(0){}
};

ostream& operator<<(ostream &c, const student &s){
    c << "Student(" << s.skill << ", " << s.index << ", " << s.team << ");";
    return c;
}

int main(){
    long long n;
    cin >> n;
    vector<student> students;
    for(long long i = 0; i<n; i++){
        int a;
        cin >> a;
        student s(a, i);
        students.push_back(s);
    }
    // sort students in decreasing order by skill
    sort(students.begin(), students.end(), 
        [](student a, student b){return a.skill > b.skill;});
    if(n < 2*MINLEN){
        // Can only have one team, so diversity is just best-worst
        cout << students[0].skill - students[n-1].skill << " " << 1 << endl;
        for(long long i = 0; i<n; i++){
            cout << 1 << " ";
        }
        cout << endl;
    }else{
        // savings[i] stores how much diversity is saved by partitioning
        // between the ith and i+1th students
        vector<long long> savings;
        for(long long i = 0; i<n-1; i++){
            savings.push_back(students[i].skill - students[i+1].skill);
        }
        //print_vec(students);
        //print_vec(savings);
        vector<long long> dp(n-(MINLEN-1), 0);
        vector<long long> split_inds;
        // We now want to max the amount of diversity we save, but if we make
        // a partition in one spot i, we cannot partition within two places
        // of i (forward or backwards).
        for(long long i = MINLEN; i<dp.size(); i++){
            long long split_val = savings[i-1] + dp[i-MINLEN];
            long long no_split_val = dp[i-1];
            // Prefer to split even if technically no benefit
            // Done to avoid runtime error if split_inds is empty.
            if(split_val >= no_split_val){
                dp[i] = split_val;
                split_inds.push_back(i-1);
            }else{
                dp[i] = no_split_val;
            }
        }
        //print_vec(dp);
        //print_vec(split_inds);
        // Total savings is now dp[dp.size()-1]
        if(split_inds.size() > 0){
            long long last_split = INFTY;
            vector<long long> cleaned_splits;
            for(long long i = split_inds.size()-1; i>=0; i--){
                if(last_split - split_inds[i] >= MINLEN){
                    cleaned_splits.push_back(split_inds[i]);
                    last_split = split_inds[i];
                }
            }
            //print_vec(cleaned_splits);
            long long idx = cleaned_splits.size() - 1;
            long long team = 1;
            for(long long i = 0; i<students.size(); i++){
                students[i].team = team;
                if(i == cleaned_splits[idx]){
                    team++;
                    idx--;
                }
            }
            cout << students[0].skill - students[n-1].skill - dp[dp.size()-1] 
                << " " << team << endl;
            sort(students.begin(), students.end(), 
                [](student a, student b){return a.index < b.index;});
            for(long long i = 0; i<students.size(); i++){
                cout << students[i].team << " ";
            }
            cout << endl;
        }else{
            cout << students[0].skill - students[n-1].skill - dp[dp.size()-1] 
                << " " << 1 << endl;
            for(long long i = 0; i<n; i++){
                cout << 1 << " ";
            }
            cout << endl;
        }
    }
    return 0;
}


