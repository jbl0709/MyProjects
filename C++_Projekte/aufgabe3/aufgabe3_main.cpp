#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include "aufgabe3.hpp"

using namespace std;

int main(int argc, const char*argv[]){
    if (argc == 2){
        vector<uint32_t> sa; 
        construct(sa, argv[1]);
        int s = sa.size();
        for (int i = 0; i < s; i++){
            cout << sa.at(i) << endl;
        }
    }
    else if(argc > 2){
        vector<uint32_t> sa; 
        vector<uint32_t> hits;
        construct(sa, argv[1]);
        for (int i = 2; i < argc; i++)
            {
            find(argv[i], sa, argv[1], hits);
            cout << argv[i] << ": ";
            sort(hits.begin(), hits.end());
            for(auto x: hits){
                cout << x << " ";
            }
            cout << '\n';  
        }
    }
    else{
        return 1;
    }
}