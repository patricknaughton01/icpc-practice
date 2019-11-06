#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

string eval(string op, string a, string b);
template<typename T>
vector<T> slice_vec(vector<T> const &vec, int start, int end);
template<typename T>
vector<T> combine_vecs(vector<T> const &a, vector<T> const &b);
char type(string elt);

template <typename T>
void print_vec(vector<T> vec){
    for(auto iter = vec.begin(); iter != vec.end(); iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

vector<string> simplify(vector<string> const &expr, vector<char> const &types){
    /*if(expr.size() < 3){
        return vector<string> empty;
    }*/
    //cout << expr.size() << endl;
    //print_vec(expr);
    if(expr.size() == 1){
        return expr;
    }else if(expr.size() == 3){
        if(types[0] == 'o' && types[1] == 'i' && types[2] == 'i'){
            return vector<string>(1, eval(expr[0], expr[1], expr[2]));
        }else{
            return expr;
        }
    }else if(expr.size() > 3){
        int operators = 0;
        int operands = 0;
        int ind = 1;
        while(operands < operators + 1){
            if(types[ind] == 'o'){
                operators++;
            }else{
                operands++;
            }
            ind++;
        }
        string op = expr[0];
        // Leave off the operator itself when simplifying
        vector<string> first = simplify(slice_vec(expr, 1, ind), slice_vec(types, 1, ind));
        vector<string> second = simplify(slice_vec(expr, ind, expr.size()), 
                slice_vec(types, ind, types.size()));
        if((first.size() == 1 && second.size() == 1) 
            && (type(first[0]) == 'i' && type(second[0]) == 'i')){
            return vector<string>(1, eval(op, first[0], second[0]));
        }else{
            vector<string> res;
            res.push_back(op);
            vector<string> c = combine_vecs(first, second);
            for(auto x : c){
                res.push_back(x);
            }
            return res;
        }
    }
    vector<string> empty;
    return empty;
}

char type(string elt){
    char t = 'o';
    for(auto e:elt){
        if(e >= 'a' && e <= 'z'){
            t = 'c';
        }
        if(e >= '0' && e <= '9'){
            t = 'i';
        }
    }
    return t;
}

template<typename T>
vector<T> combine_vecs(vector<T> const &a, vector<T> const &b){
    vector<T> res;
    for(int i = 0; i<a.size(); i++){
        res.push_back(a[i]);
    }
    for(int i = 0; i<b.size(); i++){
        res.push_back(b[i]);
    }
    return res;
}

template<typename T>
vector<T> slice_vec(vector<T> const &vec, int start, int end){
    vector<T> res;
    for(int i = start; i<end; i++){
        res.push_back(vec[i]);
    }
    return res;
}

string eval(string op, string a, string b){
    //cout << a << " " << b << endl;
    int x = stoi(a);
    int y = stoi(b);
    if(op == string("+")){
        return to_string(x + y);
    }
    if(op == string("-")){
        return to_string(x - y);
    }
    if(op == string("*")){
        return to_string(x * y);
    }
}

int main(){
    string in;
    int case_num = 1;
    while(getline(cin, in)){
        string curr;
        vector<string> elts;
        vector<char> types;
        char space = ' ';
        // o for op, c for character, i for int
        char type = 'o';
        for(auto iter = in.begin(); iter != in.end(); iter++){
            if((*iter) == space){
                elts.push_back(curr);
                types.push_back(type);
                type = 'o';
                curr = "";
            }else{
                if(*iter <= 'z' && *iter >='a'){type = 'c';}
                else if(*iter >= '0' && *iter <= '9'){type = 'i';}
                curr += *iter;
            }
        }
        elts.push_back(curr);
        types.push_back(type);
        //print_vec(elts);
        //print_vec(types);
        cout << "Case " << case_num++ << ": ";
        print_vec(simplify(elts, types));
    }
    return 0;
}


