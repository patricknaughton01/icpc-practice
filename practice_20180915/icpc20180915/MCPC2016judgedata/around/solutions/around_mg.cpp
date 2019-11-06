#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
using namespace std;

#define MAX_L 10
#define MAX_D 128
#define FILL '_'
#define DEBUG false

int main() {
    int L,D;
    cin >> L >> D;
    cin.ignore(256,'\n'); // this should clear original endline

    vector<string> song;
    vector<int> lines;   // lines[j] is index within song at which line j begins
    vector<int> beats;   // beats[k] is number of beats used on song[k] syllable
    vector<int> start;   // start[k] is the time at which song[k] begins (where start[0]=0)

    for (int j=0; j < L; j++) {
        string wordline,countline;
        getline(cin, wordline);
        getline(cin, countline);
        lines.push_back(song.size());
        istringstream ws(wordline);
        istringstream cs(countline);
        copy(istream_iterator<string>{ws}, {}, back_inserter(song));
        copy(istream_iterator<int>{cs}, {}, back_inserter(beats));
    }
    lines.push_back(song.size());

    int S = song.size();  // total number of syllables

    start.push_back(0);
    for (int j=1; j <= S; j++)    // add extra "start" time for when song is done
        start.push_back(start.back() + beats[j-1]);

    int sA(0), sB(0);  // syllable index within song
    for (int j=0; j < L; j++) {
        string lineA, lineB;
        int lastTime(start[sA]), lastCol(0);  // track when/where last syllable was placed

        while (sA < lines[j+1] || D+start[sB] < start[sA]) {
            if (DEBUG) {
                cerr << "sA=" << sA << ", sB=" << sB << endl;
                cerr << "lineA= " << lineA << endl;
                cerr << "lineB= " << lineB << endl;
            }

            if (sA == lines[j+1] || D+start[sB] < start[sA]) {    // B goes next
                if (!lineB.empty()) lineB += FILL;
                int c = lineB.size();
                c = max(c, lastCol + D+start[sB]-lastTime);
                while (lineB.size() < c) lineB += FILL;
                lastCol = c; lastTime = D+start[sB];
                lineB += song[sB];
                sB++;
            } else if (start[sA] < D+start[sB]) {   // A goes next
                if (!lineA.empty()) lineA += FILL;
                int c = lineA.size();
                c = max(c, lastCol + start[sA]-lastTime);
                while (lineA.size() < c) lineA += FILL;
                lastCol = c; lastTime = start[sA];
                lineA += song[sA];
                sA++;
            } else {     // A and B together
                if (!lineA.empty()) lineA += FILL;
                if (!lineB.empty()) lineB += FILL;
                int c = max(lineA.size(), lineB.size());
                c = max(c, lastCol + start[sA]-lastTime);
                while (lineA.size() < c) lineA += FILL;
                while (lineB.size() < c) lineB += FILL;
                lastCol = c; lastTime = start[sA];
                lineA += song[sA];
                lineB += song[sB];
                sA++; sB++;
            }
        }
        cout << lineA << endl;
        if (lineB.empty()) lineB = "/";
        cout << lineB << endl;
    }
}
