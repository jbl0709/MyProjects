
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <vector>
#include <cmath>

#include "Alignment.hpp"

using namespace std;
  
//constructor
Alignment::Alignment(const std::string& seq_v, const std::string& seq_h){
    s = seq_v;
    t = seq_h;
    computed = false;
}
//benutzerdefinierter Datentyp 
enum class Traceback{
    HORIZONTAL, VERTIKAL, DIAGONAL, HOME
};

void Alignment::compute(const int match, const int mismatch, const int gap, const bool local_align){
    computed = true;

    int n = s.size();
    int m = t.size();

    vector<vector<int>> S (m + 1, vector<int>(n + 1, 0)); // scoring matrix
    vector<vector<Traceback>> T(m + 1, vector<Traceback> (n + 1, Traceback::HOME));

    S[0][0] = 0;
    T[0][0] = Traceback::HOME;  

    if (local_align == true){ 

        //Smith Waterman

        int M; //match/mismatch -> diagonal
        int H; //mismatch -> insert -> horizontal
        int V; //mismatch -> delete -> vertikal

        int a; 
        int b;

        vector<int> best = {-1, -1, -1}; //bestes lokale Alignment, 1. score, 2. finales i, 3. finale j, wo alignment aufhört
        for(int i = 1; i < m + 1; i++){
            for (int j = 1; j < n + 1; j++){
                if (t.at(i - 1) == s.at(j - 1)){
                    M = S[i - 1][j - 1] + match;
                }
                else{
                    M = S[i - 1][j - 1] + mismatch;
                }
                H = S[i][j - 1] + gap;
                V = S[i - 1][j] + gap;
                //score 
                S[i][j] = max(max(0, M), max(H, V));
                //if(M >= H && M >=V){S[i][j] == M;}
                //traceback
                if(S[i][j] == M){T[i][j] = Traceback::DIAGONAL;}
                else if (S[i][j] == H){T[i][j] = Traceback::HORIZONTAL;}
                else if (S[i][j] == V){T[i][j] = Traceback::VERTIKAL;}
                if (S[i][j] > best.at(0)){best = {S[i][j], i, j};}
            }
        }
        score = best.at(0);
        // Koordinate in der Matrix, wo lokales alignment aufhört
        a = best.at(1);
        b = best.at(2);

        // Traceback
        // ts und tt sind wichtig für ausgabe
        ts.clear();
        tt.clear();
        Traceback temp = T[a][b];
        while(temp != Traceback::HOME){
            temp = T[a][b];    
            if(temp == Traceback::DIAGONAL){
                b -= 1; a -= 1; 
                ts = s.at(b) + ts;
                tt = t.at(a) + tt;
            }
            else if(temp == Traceback::HORIZONTAL){
                b -= 1; 
                ts = s.at(b) + ts; 
                tt = "-" + tt; 
            }
            else if (temp == Traceback::VERTIKAL){
                a -=1; 
                tt = t.at(a) + tt;
                ts = "-" + ts; 
            }
        }
    }
    else{
        // Needlemanwunsch 

        for(int i = 1; i < n + 1; i++){ S[0][i] = i * gap; T[0][i] = Traceback::HORIZONTAL;} // erste Zeile
        for(int i = 1; i < m + 1; i++){ S[i][0] = i * gap; T[i][0] = Traceback::VERTIKAL;} // erste Spalte

        int M; //match -> diagonal
        int H; //mismatch -> insert -> horizontal
        int V; //mismatch -> delete -> vertikal

        //score und traceback matrix auffüllen
        for(int i = 1; i < m + 1; i++){
            for (int j = 1; j < n + 1; j++){
                if (t.at(i - 1) == s.at(j - 1)){
                    M = S[i - 1][j - 1] + match;
                }
                else{
                    M = S[i - 1][j - 1] + mismatch;
                }
                H = S[i][j - 1] + gap;
                V = S[i - 1][j] + gap;
                //score 
                S[i][j] = max(M, max(H, V));
                //if(M >= H && M >=V){S[i][j] == M;}
                //traceback 
                if(S[i][j] == M){T[i][j] = Traceback::DIAGONAL;}
                else if (S[i][j] == H){T[i][j] = Traceback::HORIZONTAL;}
                else if (S[i][j] == V){T[i][j] = Traceback::VERTIKAL;}
            }
        }
        score = S[m][n];

        //traceback
        ts.clear();
        tt.clear();
        Traceback temp = Traceback::DIAGONAL;
        while(temp != Traceback::HOME){
            temp = T[m][n]; 
            if(temp == Traceback::DIAGONAL){
                n -= 1; m -= 1; 
                ts = s.at(n) + ts;
                tt = t.at(m) + tt;
            }
            else if(temp == Traceback::HORIZONTAL){
                n -= 1; 
                ts = s.at(n) + ts; 
                tt = "-" + tt; 
            }
            else if (temp == Traceback::VERTIKAL){
                m -=1; 
                tt = t.at(m) + tt;
                ts = "-" + ts; 
            }
        }
    }
}

int Alignment::getScore() const{
    if(computed == true){return score;}
    throw std::logic_error("no");
    return 1;
}

void Alignment::getAlignment(string& a1, string& gaps, string& a2) const{
    a1.clear();
    gaps.clear();
    a2.clear();
    if (computed == true){
        a1 = ts; 
        a2 = tt; 
        gaps = "";
        for(size_t i = 0; i < ts.size(); i++){
            if(ts.at(i) == '-' || tt.at(i) == '-' || ts.at(i) != tt.at(i)){gaps.append(" ");}
            else{gaps.append("|");}
        }
    }
    else{
        throw logic_error("no");
    }
}