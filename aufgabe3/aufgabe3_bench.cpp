// compile with Makefile: 
// $ make aufgabe3_bench
// or use
// $ g++ -std=c++17 -Wall -pedantic -O3 -D_GLIBCXX_ASSERTIONS -g -fsanitize=address aufgabe3_bench.cpp aufgabe3.cpp -o aufgabe3_bench
//
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "aufgabe3.hpp"

using Time = std::chrono::steady_clock;
using ms = std::chrono::milliseconds;
using TimePoint = std::chrono::time_point<Time, std::chrono::duration<float>>;

TimePoint getCurrentTime()
{ 
  return Time::now();
}

float timeDiffFrom(const TimePoint& earlier)
{
  return (getCurrentTime() - earlier).count();
}


using namespace std;


int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        std::cout << argv[0] << " <FASTA file> <# queries>\n"
                  << "  e.g. " << argv[0] << " Candidatus.Solibacter.usitatusEllin6076.fasta 1000000" << std::endl;
        return 1;
    }
    std::ifstream  is(argv[1]);
    if (!is.good())
    { // read file instead of treating as text
      std::cerr << "Cannot open file '" << argv[1] << "'\n";
      return 1;
    }
    
    string tmp, text;
    getline(is, tmp);  // header (optional)
    if (tmp[0] != '>') text = tmp;
    while (getline(is, tmp))
    {
      text += tmp;
    }
    std::cout << "Text length: " << text.size() << " starting with " << text.substr(0, 10) << "...\n";

    int query_count = atoi(argv[2]);
    std::cout << "Performing " << query_count << " queries\n";
    if (query_count < 1)
    {
      std::cerr << "Number of queries must be positive!\n";
      return 1;
    }
    
    vector<uint32_t> sa;
    vector<uint32_t> hits;
    
    std::cout << "Construction starts ... \n";
    auto t_construct_start_time = getCurrentTime();
    construct(sa, text);
    auto t_construct_sec = timeDiffFrom(t_construct_start_time);
    std::cout << "Construction time: " << t_construct_sec << " sec\n";

    std::cout << "Search starts ... \n";
    auto t_search_start_time = getCurrentTime();
    string query;
    long total_hits(0);
    double parts = (double)text.size() / (double)query_count;
    for (int i = 0; i < query_count; ++i)
    {
      query = text.substr(int(i * parts), 60);
      find(query, sa, text, hits);
      total_hits += hits.size();
    }
    auto t_find_sec = timeDiffFrom(t_search_start_time);
    std::cout << "Search time: " << t_find_sec << " sec for " << total_hits << " hits\n";
    
    if (query_count == 1e6)
    { // hardcoded # hits expected (only applicable to Candidatus.Solibacter.usitatusEllin6076.fasta)
      if (total_hits != 1062218)
      {
        std::cerr << "\nWrong number of hits -- go fix your code!\n";
        return 1;
      }
    }
    
    std::cout << "Total time: " << t_construct_sec + t_find_sec << " sec\n";
    
    return 0;
}
