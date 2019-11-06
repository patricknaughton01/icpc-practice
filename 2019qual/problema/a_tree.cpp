#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <memory>

using namespace std;


template <typename T>
void print_vec(vector<T> vec);
bool isOp(char a);
int convert(char a);
int eval(char op, bool a, bool b);
bool isBin(char a);


unordered_map<int, bool> vals;

class Node{
    public:
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        int val;
        Node(int x);
};

Node::Node(int x):val(x){}

Node head(-1);

template <typename T>
void print_vec(vector<T> vec){
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

void place(Node &n){
    
}

bool simplify(vector<char> &expr, int start, int end){
    
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

Node& parse(vector<char> elts)

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
    
    for(int i = elts.size()-1; i >= 0; i--){
        if(isOp(elts[i])){
            if(isBin(elts[i])){
                
            }else{
                
            }
        }
    }
    //print_vec(elts);
    if(simplify(elts, 0, elts.size())){
        cout << 'T' << endl;
    }else{
        cout << 'F' << endl;
    }
    return 0;
}


