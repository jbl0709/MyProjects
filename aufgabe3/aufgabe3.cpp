// #include <string>
// #include <vector>

// void construct(std::vector<uint32_t>& sa, const std::string& text)
// void find(const std::string& query, const std::vector<uint32_t>& sa, const std::string& text, std::vector<uint32_t>& hits);
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdint>
using namespace std; 

void construct(vector<uint32_t>& sa, const string& text){
    sa.clear(); // sa clearen, falls nicht leer
    // Lambda Funktion:
    uint32_t n = text.size();
    for(uint32_t i = 0; i < n; i++){
        sa.push_back(i);
    }
    //hilfsfunktion
    auto helpsort = [&] (const uint32_t& p1, const uint32_t& p2){
        int foo = max(p1, p2); //suche nach dem kürzeren suffix
        int sze = text.size() - foo;
        // Vergleich zwischen den iten Chars der strings. 
        for (int i = 0; i < sze; i++){
            char temp1 = text.at(p1 + i);              
            char temp2 = text.at(p2 + i);
            if(temp1 != temp2){return temp1 < temp2;} // wenn unterschiedlich in sze -1
        }
        return p1 > p2; // wenn sie bis zur sze -1 ten Stelle identisch, dann nach size()
    };

    // Vector sortieren mit sort und einfügen in sa.
    sort(sa.begin(), sa.end(), helpsort); //iteratoren
}


// Binäre Suche mit mlr-Heuristik
void find(const std::string &query, const std::vector<uint32_t> &sa, const std::string &text, std::vector<uint32_t> &hits)
{
    hits.clear();
    if (query.empty() || text.empty())
        return;

    int n = sa.size();
    int Lp;
    int M;
    int L;
    int R;

    // Find left border
    if (std::lexicographical_compare(query.begin(), query.end(), text.begin() + sa[0], text.end()) || query == text.substr(sa[0], n)) 
    {
        Lp = 0;
    }
    else if (std::lexicographical_compare(text.begin() + sa[n - 1], text.end(), query.begin(), query.end())) 
    {
        Lp = n;
    }
    else
    {
        L = 0;
        R = n - 1;
        while (R - L > 1)
        {
            M = (L + R) / 2;
            //lexicograph. compare ist true, falls query <= text.substr(sa[M])
            if (std::lexicographical_compare(query.begin(), query.end(), text.begin() + sa[M], text.end()) || query == text.substr(sa[M], n)) 
            {
                R = M;
            }
            else
            {
                L = M;
            }
        }
        Lp = R;
    }

    // Find right border
    int Rp = 0;
    L = 0;
    R = n - 1;
    while (R - L >= 0)
    {
        M = (L + R) / 2;
        if (query == text.substr(sa[M], query.size())){
            L = M+1;
            Rp = M;
        }
        else if (std::lexicographical_compare(query.begin(), query.end(), text.begin() + sa[M], text.end()))
        {
            R = M-1;
        }
        else
        {
            L = M+1;
        }
    }

    // Find the exact matches
    for (int i = Lp; i <= Rp; ++i)
    {
        if (Lp == Rp && text.compare(sa[Lp], query.size(), query) == 0){
            hits.push_back(sa[i]);
        }
        else if (Lp < Rp){
            hits.push_back(sa[i]);
        }
    }
    std::sort(hits.begin(), hits.end());
}
