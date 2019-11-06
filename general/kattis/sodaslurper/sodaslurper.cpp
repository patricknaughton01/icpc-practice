#include <iostream>
#include <cstdio>
using namespace std;

int main(){
    int bottlesStart;
    int bottlesAcquired;
    int costPerBottle;
    cin >> bottlesStart;
    cin >> bottlesAcquired;
    cin >> costPerBottle;
    //printf("%d %d %d\n", bottlesStart, bottlesAcquired, costPerBottle);
    int total = 0;
    int bottles = bottlesStart + bottlesAcquired;
    while(bottles >= costPerBottle){
        int extra = bottles % costPerBottle;
        bottles /= costPerBottle;
        total += bottles;
        bottles += extra;
    }
    cout << total << "\n";
    return 0;
}
