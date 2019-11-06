#include <iostream>
#include <vector>
#include <algorithm>

#define ABS(x) ((x)<0?(-(x)):(x))

using namespace std;

int main(){
    int N, M, P;
    cin >> N >> M >> P;
    double p_per = (double)P/100.0;
    vector<double> ratios;
    vector<long long> big_gears;
    vector<long long> small_gears;
    for(int i = 0; i<N; i++){
        long long g;
        cin >> g;
        big_gears.push_back(g);
    }
    for(int i = 0; i<M; i++){
        long long g;
        cin >> g;
        small_gears.push_back(g);
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            ratios.push_back((double)small_gears[j]/(double)big_gears[i]);
        }
    }
    sort(ratios.begin(), ratios.end(), [](double a, double b){ return a < b;});
    bool gears_good = true;
    for(int i = 0; i < ratios.size()-1; i++){
        //cout << ratios[i] << endl;
        //if(ABS((ratios[i+1]-ratios[i])/((ratios[i]+ratios[i+1])/2.0)) * 100 > P){
        //if(ABS((ratios[i+1]-ratios[i])/((ratios[i]+ratios[i+1])/2.0)) * 100 > P){
        if(ABS((ratios[i+1]-ratios[i])/(ratios[i])) * 100 > P){
            cout << "Time to change gears!" << endl;
            gears_good = false;
            break;
        }
    }
    if(gears_good){
        cout << "Ride on!" << endl;
    }
    return 0;
}
