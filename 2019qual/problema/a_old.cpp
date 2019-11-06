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
    cout << "simplify with start = " << start << " and end = " << end << " ";
    for(int i = start; i < end; i++){
        cout << expr[i] << " ";
    }
    cout << endl;
    if(end-start == 0){
        return false;
    }
    if(end-start == 1){
        return vals[convert(expr[start])];
    }
    char op = expr[end-1];
    if(op == '+' || op == '*'){
        if(end-start == 3){
            return eval(op, vals[convert(expr[start])], vals[convert(expr[start+1])]);
        }else{
            int split = getSplit(expr, start, end);
            return eval(op, simplify(expr, start, split), simplify(expr, split, end-1));
        }
    }else{
        return eval(op, simplify(expr, getNegStart(expr, start, end-1), end-1), false);
    }
}

int getSplit(vector<char> &expr, int start, int end){
    int split = start;
    vector<char> types;
    vector<char> indicies;
    cout << "Start = " << start << " end = " << end << endl;
    // v for val or group of unary ops, o for binary op
    for(int i = start; i<end; i++){
        //cout << "expr[i] = " << expr[i] << endl;
        //cout << i << " " << end << endl;
        if(!isOp(expr[i])){
            types.push_back('v');
            indicies.push_back(i);
            while(i < end && expr[i+1] == '-'){
                //cout << "i= " << i << " and expr[i+1] = " << expr[i+1] << endl;
                i++;
            }
        }else{
            if(!isBin(expr[i])){
                //cout << "Not a bin" << endl;
                types.push_back('v');
                indicies.push_back(i);
            }   
            else{
                types.push_back('o');
                indicies.push_back(i);
                while(i < end && expr[i+1] == '-'){
                    i++;
                }
            }
        }
        //print_vec(types);
    }
    print_vec(types);
    int num_bin = 0;
    for(int i = types.size() - 1; i >= 0; i--){
        if(types[i] == 'o'){
            num_bin++;
        }
    }
    if(num_bin==1){
        split = indicies[indicies.size()-1]-1; 
    }
    else{
        for(int i = types.size()-1; i >= 1; i--){
            if(types[i] == 'v' && types[i-1] == 'v'){
                split = indicies[i-1];
                break;
            }
        }
    }
    return split;
}

int getNegStart(vector<char> &expr, int start, int end){
    int newStart = start;
    for(int i = end-1; i >= start + 1; i--){
        if(isBin(expr[i])){
            return getSplit(expr, start, i+1);
        }else if(!isOp(expr[i])){
            return i;
        }
    }
    return newStart;
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
    cout << "first split: " << getSplit(elts, 0, elts.size()-1) << endl;
    //print_vec(elts);
    if(simplify(elts, 0, elts.size())){
        cout << 'T' << endl;
    }else{
        cout << 'F' << endl;
    }
    return 0;
}


