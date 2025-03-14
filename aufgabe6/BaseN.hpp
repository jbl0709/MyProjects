//
//
//
//
//
//      DO NOT MODIFY THIS FILE !!!!!
//
//
// 
#pragma once

#include <string>

/**

  Class to convert numbers between different bases and apply a two-complement when in base 2.
   
*/
class BaseN 
{
public:
    /**
       @brief Convert a natural number from base N to the equivalent in base M
       
       Depending on the input base 'N', valid characters are 0-9 and A-F, i.e. up to base 16.
       
       @param number_baseN Input number in base N
       @param N The base of the input number
       @param M The base of the output number
       @return A number of base M
       
       @throw std::invalid_argument if either N or M are less than 2 or larger than 16
       @throw std::invalid_argument if the input contains invalid characters for the input base 
    */
    static std::string convert(const std::string& number_baseN, int N, int M);          
    
    
    /**
      @brief Compute the two-complement of a number given as a binary string (individual bits)
      
      Two-complement inverts all bits and adds 1.
      
      @param in The bit pattern (number) to apply two-complement to
      @param size The number of valid bits (e.g. 32)
      @return The negated number with at exactly @p size bits.
    
      @throw std::invalid_argument if either
            + string contains anything except '0' or '1'
            + or the input @p in is longer than @p size.
    */
    static std::string twoComplement(const std::string& in, int size);
    
    
    /**
      @brief Tell if a number in base2 given as a string is a negative number (i.e. is in Two-complement form).
      
      The number of bits is given in @p size. The input may be shorter (i.e. can omit leading zeros).
      
      @return true if the number is negative, false otherwise
      @throw std::invalid_argument if 
                  + the input contains invalid characters (other than 0/1)
                  + or the input @p in is longer than @p size.
    
    */
    static bool isNegativeNumberBase2(const std::string& in, int size);
    
    
    ////////////////////////////
    //// BONUS TASK: 
    ////////////////////////////
    
    /**
      @brief Adds two integer numbers a and b, both of base N (as long as the result is positive).
      
      Note: 'a' and/or 'b' may be negative, i.e. contain a leading '-'.
      
      This function only defined if the result of a+b is positive.

      @param a Number a
      @param b Number b
      @param baseN Base of @p a and @p b
      @return a+b in baseN
      @throw std::invalid_argument if 
              + the input contains invalid characters (other than '-' and characters for the @p baseN)
              + if the result is negative
    */
    static std::string add(const std::string& a, const std::string& b, int baseN);
    
};

