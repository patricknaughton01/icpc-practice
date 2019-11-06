#include<iostream>
#include<string>
#include<cmath>
using namespace std;

string octToBin(string octStr);
string binToHex(string binStr);
string octDigitToBin(char octDig);

int main(){
    string input;
    getline(cin, input);
    //cout << octToBin(input) << endl;
    //cout << binToHex(input) << endl;
    cout << binToHex(octToBin(input)) << endl;
    return 0;
}

string octToBin(string octStr){
    string binStr = "";
    for(int i = 0, n = octStr.size(); i<n; i++){
        string expansion = octDigitToBin(octStr[i]);
        for(int j = 0; j<expansion.size(); j++){
            binStr.push_back(expansion[j]);
        }
    }
    return binStr;
}

string binToHex(string binStr){
    string rhexStr = "";
    // start at lsd and go in groups of 4
    for(int i = binStr.size()-1; i>-1; i-=4){
        int decOut = 0;
        for(int j = 0; j<4 && (i-j)>-1; j++){
            decOut += pow(2, j)*(int)(binStr[i-j] - '0');
            //cout << "Binstr: " << binStr[i-j] << endl;
            //cout << "Dec out: " << decOut << endl;
        }
        if(decOut < 10){
            rhexStr.push_back((char)(decOut + '0'));
        }else{
            char dig = 'A';
            switch(decOut){
                case 11:
                    dig = 'B';
                    break;
                case 12:
                    dig = 'C';
                    break;
                case 13:
                    dig = 'D';
                    break;
                case 14:
                    dig = 'E';
                    break;
                case 15:
                    dig = 'F';
                    break;
            }
            rhexStr.push_back(dig);
        }
    }
    string fhexStr = "";
    for(int i = rhexStr.size()-1; i>-1; i--){
        fhexStr.push_back(rhexStr[i]);
    }
    string hexStr = "";
    if(fhexStr.size()>1){
        int ind = 0;
        int n = fhexStr.size();
        while(ind < n && fhexStr[ind] == '0'){ind++;}
        for(int i = ind; i<n; i++){
            hexStr.push_back(fhexStr[i]);
        }
    }else{
        hexStr = fhexStr;
    }
    return hexStr;
}

string octDigitToBin(char octDig){
    int octInt = (int)(octDig - '0');
    string fours = "0";
    string twos = "0";
    string ones = "0";
    if(octInt >= 4){
        octInt -= 4;
        fours = "1";
    }
    if(octInt >= 2){
        octInt -= 2;
        twos = "1";
    }
    if(octInt >= 1){
        ones = "1";
    }
    return fours+twos+ones;
}
