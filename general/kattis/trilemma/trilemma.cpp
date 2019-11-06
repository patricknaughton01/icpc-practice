#include<iostream>
#include<array>
#include<cstdio>
using namespace std;

class Triangle{
    public:
        int points[3][2];
        
        Triangle(int ps[3][2]){
            for(int i = 0; i<3; i++){
                printf("[%d, %d]", ps[i][0], ps[i][1]);
            }
        }
};

int main(){
    int test[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    Triangle t(test);
    return 0;
}


