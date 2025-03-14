#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <cstring>
#include <string>
#include <utility>
#include "Float.hpp"

using namespace std;

int main(int argc, const char* argv[]){
    Float f;
    char mode = argv[1][0]; // da wir nicht char = string setzen können
    if(mode == 'a'){
        //stof wird benutzt, um String in Float umzuwandeln
        float res = f.gapAfter(stof(argv[2]));
        cout << "Gap to the float number following " << argv[2] << " is " << res << endl;
    }
    else if(mode == 'b'){
        float res = f.firstGapOf(stof(argv[2]));
        cout << "First Gap of " << argv[2] << " or larger is between: " << res << " and its successor." << endl;
    }
    else if(mode == 'c'){
        vector<float> vec;
        for(int i = 3; i < argc; i++){
            vec.push_back(stof(argv[i]));
        }
        // strcmp, statt die speicheraddressen zu vergleichen auf die sie zeigen, 
        // werden hier die Strings verglichen durhc strcmp.
        if(strcmp(argv[2], "naive") == 0){ 
            float res = f.summation(vec, Float::SUMMATION::NAIVE);
            cout << "Adding: " << vec.at(0);
            for (size_t i = 1; i < vec.size(); i++){
                cout << " + " << vec.at(i);
            }
            cout << " ---> " << res << endl;
        }
        else if(strcmp(argv[2], "reorder") == 0){
            float res = f.summation(vec, Float::SUMMATION::REORDER);
            sort(vec.begin(), vec.end());
            cout << "Adding: " << vec.at(0);
            for (size_t i = 1; i < vec.size(); i++){
                cout << " + " << vec.at(i);
            }
            cout << " ---> " << res << endl;
        }
    }
}