/*
#include "Float.hpp"
#include <iostream> 
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm> 
#include <cmath> 
#include <cfloat>
#include <limits>
#include <unordered_map>

using namespace std;

float Float::gapAfter(const float num){
    if (isnan(num)|| isinf(num)){return NAN;}
    float next = nextafter(num, INFINITY);
    return next - num; 
}

float Float::firstGapOf(const float min_gap_size){
    if(min_gap_size <= 0.0f || isnan(min_gap_size)){return NAN;}                       
    else if(min_gap_size > numeric_limits<float>::max()){return INFINITY;}
    float num = numeric_limits<float>::min();
    float gap = numeric_limits<float>::min();
    while(gap < min_gap_size){
        num = num*2; // da float = (-1)^sign x mantisse x 2^exponent erhöht num*2 exponent um 1.
        gap = gapAfter(num); 
    }
    return num;
}

float Float::summation(const std::vector<float>& nums, const SUMMATION type){
    if(type == SUMMATION::NAIVE){
        float sum = 0.0f;
        for(size_t i = 0; i < nums.size(); i++){
            sum += nums.at(i); //Addition nacheinander ohne Sortieren
        }
        return sum;
    }
    else if(type == SUMMATION::REORDER){
        float sum = 0.0f;
        vector<float> numsort = nums;
        sort(numsort.begin(), numsort.end());
        for(size_t i = 0; i < numsort.size(); i++){sum += numsort.at(i);}
        return sum;
    }
    else if(type == SUMMATION::KAHAN){
        return 0;
    }
    else{
        return NAN;
    }
}
*/
#include "Float.hpp"
#include <iostream> 
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm> 
#include <cmath> 
#include <cfloat>
#include <limits>
#include <unordered_map>

using namespace std;

float Float::gapAfter(const float num){
    if (isnan(num)|| isinf(num)){return NAN;}
    float next = nextafter(num, INFINITY);
    return next - num; 
}

float Float::firstGapOf(const float min_gap_size){
    if(min_gap_size <= 0.0f || isnan(min_gap_size)){return NAN;}                       
    float num = numeric_limits<float>::min();
    float gap = numeric_limits<float>::min();
    //if(min_gap_size == numeric_limits<float>::min()){return 0.0f;}
    while(gap < min_gap_size){
        num = num*2; 
        gap = gapAfter(num); 
    }
    return num;
}

float Float::summation(const std::vector<float>& nums, const SUMMATION type){
    if(type == SUMMATION::NAIVE){
        float sum = 0.0f;
        for(size_t i = 0; i < nums.size(); i++){
            sum = sum + nums.at(i);
        }
        return sum;
    }
    else if(type == SUMMATION::REORDER){
        float sum = 0.0f;
        vector<float> numsort = nums;
        sort(numsort.begin(), numsort.end());
        for(size_t i = 0; i < numsort.size(); i++){
            sum = sum + numsort.at(i);
        }
        return sum;
    }
    else if(type == SUMMATION::KAHAN){
        return 0;
    }
    else {
        return NAN;
    }
}
