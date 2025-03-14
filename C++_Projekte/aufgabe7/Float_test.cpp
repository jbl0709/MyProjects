#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>


#include "Float.hpp"

#include <iomanip>

using namespace std;

typedef int opt_score;
typedef int has_score;
typedef pair<has_score, opt_score> TRT; // test return-type

template <typename FUNC>
void report(int& points, FUNC fn, const string& testname)
{
  std::cout << "##########################\ntest function '" << testname << "' ...\n";
  TRT new_score;
  try {
    new_score = fn(); // call the function
  }
  catch (...)
  {
    std::cout << "Error: test function '" << testname << "' threw unexpected exception\n";
  }
  points += new_score.first;
  std::cout << "Test: '" << testname << "' [" << new_score.first << "/" << new_score.second  << "]\n"
            << "current points: " << points << "\n\n";
  return;
}


TRT test_gapAfter()
{
  int points(0);
  float res;

  // border cases
  res = Float::gapAfter(+INFINITY);
  points += std::isnan(res);

  res = Float::gapAfter(std::numeric_limits<double>::quiet_NaN());
  points += std::isnan(res);

  res = Float::gapAfter(std::numeric_limits<float>::max());  // gap to infinity
  points += std::isinf(res);

  // real values
  res = Float::gapAfter(0.0f);
  points += (res < std::numeric_limits<float>::min()); // it's a denormal...

  res = Float::gapAfter(10.0f);
  points += (res == 9.5367431640625e-07f);

  res = Float::gapAfter(1e2f);
  points += (res == 7.62939453125e-06f); // 100.00000762939453125

  res = Float::gapAfter(1e3f);
  points += (res == 6.10351563e-05f); // 1000.00006103515625

  res = Float::gapAfter(0b1111111111);
  points += (res == 6.10351563e-05f); // 1023.0000000000001137

  res = Float::gapAfter(1e10f);
  points += (res == 1024.0f);  // 10000001024.0f)

  res = Float::gapAfter(1e36f);
  points += (res == 7.92281625e+28f); // 1.0000000409184787596e+36

  
  return make_pair(points / 5, 2);
}

TRT test_firstGapOf()
{
  int points = 0;
  float res;

  // border cases
  res = Float::firstGapOf(-0.25f);
  points += std::isnan(res);
  res = Float::firstGapOf(+INFINITY);
  points += (res >= std::numeric_limits<float>::max());

  // real data
  res = Float::firstGapOf(0.25f);
  points += (res == 2097152.0f);
  
  res = Float::firstGapOf(0.5f);
  points += (res == 4194304.0f);

  res = Float::firstGapOf(1.0f);
  points += (res == 8388608.0f);

  res = Float::firstGapOf(2.0f); // skip an integer
  points += (res == (1 << 24)); // == 16777216 ( == 2^24 == number of bits of float's mantissa) --> 16777217 is not representable in float

  res = Float::firstGapOf(15.0f);   // same gap is actually 16
  points += (res == 134217728.0f);

  res = Float::firstGapOf(1e4);  // huge gap (16384 to be precise)
  points += (res == 137438953472.0f);

  return make_pair(points / 2, 4);
}

TRT test_summation()
{
  int points = 0;
  float res;

  // CASE 1:
  std::vector<float> nums{ 16777216, 0.25, 0.25, 0.25, 0.25, 0.9 }; // 16777217.9 (in theory...)
  res = Float::summation(nums, Float::SUMMATION::NAIVE);
  points += (res == 16777216); // adding the small stuff never had any effect

  res = Float::summation(nums, Float::SUMMATION::REORDER); // reordering by size helps a lot, since we can accumulate 1.9 before adding the big one
  points += (res == 16777218); // success (16777218 is the direct successor of 16777216 in float)!

  // CASE 2:
  nums = std::vector<float>(10, 0.1f); // sums up to 1 (in theory...)
  res = Float::summation(nums, Float::SUMMATION::NAIVE);
  points += (res == 1.0000001192092895508); // nope...

  res = Float::summation(nums, Float::SUMMATION::REORDER); // reordering by size does not help here
  points += (res == 1.0000001192092895508); // nope...

  return make_pair(points, 4);
}

TRT test_summationBONUS()
{
  int points = 0;
  
  try {
    std::vector<float> nums(10, 0.1f); // sums up to 1 (in theory...)
    float res = Float::summation(nums, Float::SUMMATION::KAHAN);
    points += 3*(res == 1.0f); // we've lost the   1e-35f
  }
  catch (...)
  {
    // not implemented...
  }
  return make_pair(points, 3);
}


int main(int argc, const char * argv[])
{
  int points = 0;

  report(points, &test_gapAfter, "test_gapAfter");         // 2
  report(points, &test_firstGapOf, "test_firstGapOf");     // 4
  report(points, &test_summation, "test_summation");       // 4
  report(points, &test_summationBONUS, "test_summationBONUS");       // 2

  
  std::cout << "Final score: " << points << " / 10\n\n";

  return 100 + points;
}