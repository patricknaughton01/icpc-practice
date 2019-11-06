#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <unordered_map>

using namespace std;


template <typename T>
void print_vec(vector<T> vec);
bool isOp(char a);
bool simplify(vector<string> &expr, int start, int end);
int convert(char a);
int eval(char op, bool a, bool b);
int getSplit(vector<char> &expr, int start, int end);
bool isBin(char a);
int getNegStart(vector<char> &expr, int start, int end);


unordered_map<int, bool> vals;

template <typename T>
void print_vec(vector<T> vec){
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

bool simplify(vector<char> &expr, int start, int end){
    /*cout << "simplify with start = " << start << " and end = " << end << " ";
    for(int i = start; i < end; i++){
        cout << expr[i] << " ";
    }
    cout << endl;*/
    if(end-start == 0){
        return false;
    }
    if(end-start == 1){
        return vals[convert(expr[start])];
    }
    if(isBin(expr[end-1])){
        int i;
        int bin_seen = 0;
        int val_seen = 0;
        int split;
        for(i = end-2; i>=start; i--){
            if(!isOp(expr[i])){
                val_seen++;
            }
            if(isBin(expr[i])){
                bin_seen++;
            }
            if(val_seen == bin_seen+1){
                split = i;
                break;
            }
            //cout << "bin seen: " << bin_seen << endl;
            //cout << "val seen: " << val_seen << endl;
        }
        bool left = simplify(expr, split, end-1);
        bool right = simplify(expr, start, split);
        return eval(expr[end-1], right, left);
    }else if(isOp(expr[end-1])){
        return eval(expr[end-1], simplify(expr, start, end-1), false);
    }else{
        return vals[convert(expr[end-1])];
    }
}

bool isBin(char a){
    return a == '+' || a == '*';
}

bool isOp(char a){
    return a == '-' || a == '+' || a == '*';
}

int convert(char a){
    return a - 'A';
}

int eval(char op, bool a, bool b){
    if(op == '-'){
        return !a;
    }
    if(op == '+'){
        return a || b;
    }
    else{
        return a && b;
    }
}

int main(){

    int n;
    char val;
    cin >> n;
    for(int i = 0; i<n; i++){
        cin >> val;
        if(val == 'T'){
            vals[i] = true;
        }else{
            vals[i] = false;
        }
    }
    
    char in;
    vector<char> elts;
    while(cin >> in){
        elts.push_back(in);
    }
    //print_vec(elts);
    if(simplify(elts, 0, elts.size())){
        cout << 'T' << endl;
    }else{
        cout << 'F' << endl;
    }
    return 0;
}


