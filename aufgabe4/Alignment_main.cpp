#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "Alignment.hpp"

using namespace std;


int main(int argc, const char* argv[])
{
    Alignment a(argv[1], argv[2]);
    string gaps;
    string a1; 
    string a2;
    
    if (argc == 3)
    {
      a.compute(3, -1, -2, false);
      a.getAlignment(a1, gaps, a2);
      cout << a1 << endl;
      cout << gaps << endl;
      cout << a2 << endl;
      cout << "score: " << a.getScore();
    }
    else if(argc == 6){

      int match = stoi(argv[3]);
      int mismatch = stoi(argv[4]);
      int gap = stoi(argv[5]);

      a.compute(match, mismatch, gap, false);
      a.getAlignment(a1, gaps, a2);

      cout << a1 << endl;
      cout << gaps << endl; 
      cout << a2 << endl;
      cout << "score: " << a.getScore();
    }
    else if(argc == 7){
      int match = stoi(argv[3]);
      int mismatch = stoi(argv[4]);
      int gap = stoi(argv[5]);

      a.compute(match, mismatch, gap, true);
      a.getAlignment(a1, gaps, a2);

      cout << a1 << endl;
      cout << gaps << endl; 
      cout << a2 << endl;
      cout << "score: " << a.getScore();
    }

    else{
      throw std::logic_error("no");
      return 1;
    }
}
