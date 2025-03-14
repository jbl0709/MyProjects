#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <string>
#include <utility>
#include <fstream>
#include "QGramIndex.hpp"
#include "a5_util.hpp"

using namespace std;

int main(int argc, const char* argv[]){
    string text;
    ifstream myfile(argv[1]);
    if(myfile.is_open()){
        getline(myfile, text);
    }
    for(int i = 0; i < text.size(); i++){
        if(text.at(i) != 'A' && text.at(i) != 'C' && text.at(i) != 'G' && text.at(i) != 'T'){throw invalid_argument ("not in DNA");}
    }

    QGramIndex qri (text, strlen(argv[2]));

    int n = qri.hash(argv[2]);
    cout << argv[2] << ": ";
    for(int x : qri.getHits(n)){
        cout << x << " ";
    }
}