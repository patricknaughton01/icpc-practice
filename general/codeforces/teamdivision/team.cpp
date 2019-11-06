#include <iostream>
#include <vector>
#include <algorithm>

#define INFTY 1000000000000000000
#define MINLEN 3

using namespace std;

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

long long min_partition(vector<student> &s, long long start, long long end){
    
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
    sort(students.begin(), students.end(), [](student a, student b){return a.skill > b.skill;});
    /*for(long long i = 0; i<n; i++){
        cout << students[i] << endl;
    }*/
    vector<long long> dp(n+1, 0);
    dp[n] = INFTY;
    // min diversity of smallest end team is third to last student minus
    // last student b/c in sorted order
    long long last_div = students[n-MINLEN].skill - students[n-1].skill;
    for(long long i = n-1; i>=n-MINLEN; i--){
        dp[i] = last_div;
    }
    for(long long i = n-MINLEN; i>=0; i--){
        long long min_div = INFTY;
        for(long long j = i+MINLEN-1; j < n; j++){
            long long div;
            if(n - j > MINLEN){
                // We can consider partitioning into a new team
                div = students[i].skill - students[j].skill;
                div += dp[j+1];
                if(div < min_div){
                    min_div = div;
                }
            }else{  // only enough for one team
                div = students[i].skill - students[n-1].skill;
                if(div < min_div){
                    min_div = div;
                }
                j = n-1;
                break;
            }
        }
        dp[i] = min_div;
    }
    long long team = 1;
    long long last_ind = 0;
    students[0].team = team;
    for(long long i = 1; i<n; i++){
        if((dp[last_ind] - dp[i] == students[last_ind].skill - students[i-1].skill) 
            && i <= n-MINLEN){
            team++;
            last_ind = i;
        }
        students[i].team = team;
    }
    sort(students.begin(), students.end(), [](student a, student b){return a.index < b.index;});
    cout << dp[0] << " " << team << endl;
    for(long long i = 0; i<students.size(); i++){
        cout << students[i].team << " ";
    }
    cout << endl;
    return 0;
}


