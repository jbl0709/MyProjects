#include <iostream> 
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm> 
#include <cmath> 
#include <unordered_map>
#include "QGramIndex.hpp"
//#include "a5_util.hpp"

using namespace std;

QGramIndex::QGramIndex(const std::string& text, const uint8_t q) : ptext(text) // referenz initialisiert
{
    qq = q; 
    if (q <= 1 || q > 13){throw invalid_argument("Invalid q!");}

    int n = text.size();
    int m = static_cast<int>(pow(4,q)); // typumwandlungsoperator, der sichere konvertierung zwischen kompatiblen datentypen erlaubt

    // q Gram Index erstellen
    int j;
    suftab.clear(); // sa clearen, falls nicht leer
    dir.clear();
    for(int i = 0; i <= m; i++){
        dir.push_back(0);
        suftab.push_back(0);
    }
    for(int i = 0; i <= n - q; i++){
        j = hash(text.substr(i, q));
        dir.at(j) += 1; 
    }
    for(int i = 1; i <= m; i++){
        dir[i] += dir[i - 1];
    }
    // Suftab hat noch überflüssige nullen. Sollten weg!
        for(int i = 0; i <= n-q; i++){
        j = hash(text.substr(i, q));
        dir.at(j) -= 1; 
        suftab.at(dir.at(j)) = i;     
    }
}

const string& QGramIndex::getText() const{
    return ptext; 
}
uint8_t QGramIndex::getQ() const{
    return qq;
}

uint32_t QGramIndex::hash(const std::string& qgram) const{
    int hwert = 0; 
    int n = qgram.size();
    int x = 0; 
    if (n <= 1 || n > 13){throw invalid_argument("Invalid q!");}
    for (int i = 0; i < n; i++){
        if(qgram.at(i)  == 'A') {x = 0;}
        else if(qgram.at(i)  == 'C') {x = 1;}
        else if(qgram.at(i)  == 'G') {x = 2;}
        else if(qgram.at(i)  == 'T') {x = 3;}
        hwert += x*pow(4, n - 1 - i);
    }
    return hwert;
}
uint32_t QGramIndex::hashNext(const uint32_t prev_hash, const char new_pos) const {
    int rollh = prev_hash; 
    int x = 0; 

    // Bestimme den Wert für das neue Zeichen (A, C, G, T)
    if (new_pos == 'A') {
        x = 0;
    } else if (new_pos == 'C') {
        x = 1;
    } else if (new_pos == 'G') {
        x = 2;
    } else if (new_pos == 'T') {
        x = 3;
    }

    rollh <<= 2;  
    rollh |= x; 
    rollh %= static_cast<int> (pow(4, qq)); // modulo rechnen
    return rollh;   
}


std::vector<uint32_t> QGramIndex::getHits(const uint32_t h) const{
    if (h < 0 || h > static_cast<uint32_t>(pow(ptext.size(), qq))){throw std::invalid_argument("Invalid hash!");}
    vector<uint32_t> hits = {}; 
    for(int i = dir.at(h); i < dir.at(h+1); i++){
        hits.push_back(suftab.at(i));
    }
    return hits;    
}

