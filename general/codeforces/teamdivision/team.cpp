#include <iostream>
#include <vector>
#include <algorithm>

#define INFTY 1000000000000000000
#define MINLEN 3
#define MIN(x, y) ((x)<(y)?(x):(y))

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

long long eval_partition(const vector<student> &s, 
    const vector<long long> &dp, long long i, long long p){
    return dp[p+1] + s[i].skill - s[p].skill;
}

long long min_partition(const vector<student> &s, const vector<long long> &dp, 
    long long i, long long start, long long end)
{
    if(end <= start){
        return -1;
    }
    if(end - start == 1){
        return start;
    }
    long long mid = (end - start)/2 + start;
    //cout << "Start: " << start << " Mid: " << mid << " End: " << end << endl;
    long long mid_p = eval_partition(s, dp, i, mid);
    long long mid_r_p = eval_partition(s, dp, i, mid+1);
    long long mid_l_p = eval_partition(s, dp, i, mid-1);
    if(mid_p <= mid_r_p && mid_p <= mid_l_p){
        // mid is min ==> we found the min
        return mid;
    }else if(mid_l_p < mid_p){
        return min_partition(s, dp, i, start, mid);
    }else{
        return min_partition(s, dp, i, mid+1, end);
    }
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
        /*long long min_div = INFTY;
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
        dp[i] = min_div;*/
        //cout << i + MINLEN -1 << " " << n-MINLEN << endl;
        long long ind = min_partition(students, dp, i, i+MINLEN-1, n-MINLEN + 1);
        if(ind == -1){
            dp[i] = students[i].skill - students[n-1].skill;
        }else{
            dp[i] = MIN(eval_partition(students, dp, i, ind), 
                students[i].skill - students[n-1].skill);
        }
    }
    /*for(long long i = 0; i<dp.size(); i++){
        cout << dp[i] << endl;
    }*/
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


