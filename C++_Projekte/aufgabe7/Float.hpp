#pragma once

#include <vector>
#include <cstdint>

/**

  Class to explore floating point behaviour.
   
*/
class Float 
{
public:
    // AS ALWAYS: DO NOT CHANGE THE INTERFACE!
    
    /**
       @brief Return the size of the gap between the given float @p num and the next floating point number (towards +infinity)

       If the input is 'NaN' or 'Inf', return 'NaN';

       See https://en.cppreference.com/w/cpp/numeric/math/nextafter for details.

       @param num The 'left' float of the gap

       @return The size of the gap
    */
    static float gapAfter(const float num);
    
    
    /**
      @brief Find the smallest float which has a gap of at least the given size
             towards its next neighbor (towards infinity).

      If the gap size is too large for type 'float' or <=0, return NaN.
      
      @param min_gap_size The minimum gap size between two floats

      @return The smallest float which has a gap of at least @p min_gap_size towards it's right neighbor
    */
    static float firstGapOf(const float min_gap_size);

    enum class SUMMATION : uint8_t
    {
      NAIVE,
      REORDER,
      KAHAN
    };

    /**
     * @brief Sums up the given numbers, just using floats (not doubles)
     *
     * Internally uses either
     *  NAIVE: sums up numbers in order
     *  REORDER: orders numbers smallest to largest and then sum up
     *  KAHAN: applies KAHAN summation method (BONUS task)
     *
     *
     * @param nums The numbers to sum up
     * @param type Summation strategy
     * @return the sum
     *
     * @throws invalid_value if SUMMATION::KAHAN is not implemented
    */
    static float summation(const std::vector<float>& nums, const SUMMATION type);



};

