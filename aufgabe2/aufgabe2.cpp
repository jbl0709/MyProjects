#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map> 
#include <algorithm>
#include "aufgabe2.h"

using namespace std;

void Horspool::setPattern(const string & pat){
    int patlength = pat.length();
    for(int i = 0; i < patlength; i++){
        if((patlength - 1 - i) == 0){
            if(tabelle.find(pat.at(i)) != tabelle.end()){
                continue;
            }
            else{ 
                tabelle[pat.at(i)] = patlength;
            }
        }
        else{
            tabelle[pat.at(i)] = (patlength - 1) - i;
        }
    }
    pattern = pat;
}
const string & Horspool::getPattern() const{
    return pattern;
}
vector<size_t> Horspool::getHits(const string & text) const {
    vector<size_t> Hits{};
    int i = 0; 
    int length = text.length() - pattern.length();
    while(i <= length){
        alignCheck_(i);
        int j = pattern.length() - 1;
        for(; j >= 0; j--){
            if(pattern.at(j) == text.at(i + j)){
                if(j == 0){
                    Hits.push_back(i); 
                    i += getShift_(text.at(i + pattern.length() - 1));
                    break;
                }
            }
            else{ 
                i += getShift_(text.at(i + pattern.length() - 1));
                break;
            }
        }
    }
    return Hits;
}
uint32_t Horspool::getShift_(const char last_char) const {
    auto temp = tabelle.find(last_char);
    if(temp != tabelle.end()){
        return temp->second;
    }
    else 
        return pattern.length();
}