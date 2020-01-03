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

struct problem{
    long long time;
    long long mand;
    problem(long long t, long long m):time(t), mand(m){}
};

ostream& operator<<(ostream &c, const problem &p){
    c << "(" << p.time << "," << p.mand << ")";
    return c;
}

long long num_probs(long long num_easy, long long num_hard, long long total_time, long long a, long long b){
    if(num_easy * a >= total_time){
        return total_time/a;
    }else{
        return MIN(num_easy + (total_time - num_easy*a)/b, num_easy+num_hard);
    }
}

int main(){
    long long m;
    cin >> m;
    for(long long i = 0; i<m; i++){
        long long n, T, a, b;
        cin >> n >> T >> a >> b;
        vector<int> types;
        vector<long long> mands;
        long long num_easy = 0, num_hard = 0;
        for(long long j = 0; j<n; j++){
            int val;
            cin >> val;
            if(val == 0){
                num_easy++;
            }else{
                num_hard++;
            }
            types.push_back(val);
        }
        for(long long j = 0; j<n; j++){
            long long val;
            cin >> val;
            mands.push_back(val);
        }
        
        vector<problem> problems;
        for(long long j = 0; j<n; j++){
            long long time = types[j] == 0 ? a:b;
            problem p(time, mands[j]);
            problems.push_back(p);
        }
        sort(problems.begin(), problems.end(), [](problem p1, problem p2){return p1.mand < p2.mand;});
        problem end(0, T);
        problems.push_back(end);
        //print(problems.begin(), problems.end());
        long long max_score = 0;
        long long must_solve_time = 0;
        long long used_hard = 0, used_easy = 0;
        for(long long j = 0; j<problems.size(); j++){
            max_score = MAX(max_score, num_probs(num_easy-used_easy, num_hard-used_hard, problems[j].mand-must_solve_time-1, a, b) + used_easy + used_hard);
            if(problems[j].time == a){
                used_easy++;
            }else{
                used_hard++;
            }
            must_solve_time += problems[j].time;
            //cout << "Stats: " << max_score << " " << used_easy << " " << used_hard << " " << must_solve_time << endl;
        }
        max_score = MAX(max_score, used_easy + used_hard - 1);
        cout << max_score << endl;
    }
    return 0;
}
