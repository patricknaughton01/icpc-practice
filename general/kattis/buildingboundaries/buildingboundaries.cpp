#include <iostream>
#include <vector>

#define MAX(x, y) ((x)>(y)?(x):(y))
#define MIN(x, y) ((x)<(y)?(x):(y))

using namespace std;

template <typename T>
void print_vec(vector<vector<T> > vec){
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        for(auto iter1 = iter->begin(); iter1 != iter->end(); iter1++){
            cout << *iter1 << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    long long T;
    cin >> T;
    vector<vector<int> > all_dims;
    for(long long i = 0; i<T; i++){
        vector<int> dims;
        for(long long j = 0; j<6; j++){
            long long d;
            cin >> d;
            dims.push_back(d);
        }
        //vector<vector<int>> all_perms;
        long long min_area;
        for(long long i = 0; i<8; i++){
            long long a1 = dims[0], b1 = dims[1], a2 = dims[2], 
                b2 = dims[3], a3 = dims[4], b3 = dims[5];
            long long tmp;
            if(i & 1){  // Check lsb
                tmp = a1;
                a1 = b1;
                b1 = tmp;
            }
            if(i & 2){  // Check next bit
                tmp = a2;
                a2 = b2;
                b2 = tmp;
            }
            if(i & 4){  // Check next bit
                tmp = a3;
                a3 = b3;
                b3 = tmp;
            }
            
            // Test the four cases:
            long long area1 = (a1 + a2 + a3) * MAX(MAX(b1, b2), b3);
            long long area2 = (a1 + MAX(a2, a3)) * (MAX(b1, b2 + b3));
            long long area3 = (a2 + MAX(a1, a3)) * (MAX(b2, b1 + b3));
            long long area4 = (a3 + MAX(a2, a1)) * (MAX(b3, b2 + b1));
            if(i == 0){
                min_area = MIN(MIN(MIN(area1, area2), area3), area4);
            }else{
                min_area = MIN(MIN(MIN(MIN(area1, area2), area3), area4), min_area);
            }
        }
        cout << min_area << endl;
    }
    //print_vec(all_dims);
    
    return 0;
}
