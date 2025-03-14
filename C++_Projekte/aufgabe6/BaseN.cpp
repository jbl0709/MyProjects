#include "BaseN.hpp"
#include <stdexcept>
#include <cmath>
#include <unordered_map>

std::string BaseN::convert(const std::string& number_baseN, int N, int M) 
{
    std::unordered_map<char,int> vc;
    vc['0'] = 0;
    vc['1'] = 1;
    vc['2'] = 2;
    vc['3'] = 3;
    vc['4'] = 4;
    vc['5'] = 5;
    vc['6'] = 6;
    vc['7'] = 7;
    vc['8'] = 8;
    vc['9'] = 9;
    vc['A'] = 10;
    vc['B'] = 11;
    vc['C'] = 12;
    vc['D'] = 13;
    vc['E'] = 14;
    vc['F'] = 15;

    if ( N < 2 || N > 16) {throw std::invalid_argument("Invalid N"); }
    if ( M < 2 || M > 16) {throw std::invalid_argument("Invalid M"); }

    std::string result = "";
    int temp = 0; 
    int curr = 0;
    
    if (N > 10) 
    {
        for (size_t i = 0; i < number_baseN.length(); i++) 
        {
            if (vc.find(number_baseN[i]) != vc.end()) {temp += vc[number_baseN[i]]*pow(N,number_baseN.length()-1-i);}
            else {throw std::invalid_argument("Invalid number_baseN"); }
        }
    }
    else 
    {
        for (size_t i = 0; i < number_baseN.length(); i++)
        {
            if (vc.find(number_baseN[i]) != vc.end())
            {
                if(vc[number_baseN[i]] < 10) {temp += vc[number_baseN[i]]*pow(N,number_baseN.length()-1-i);}
                else {throw std::invalid_argument("Invalid number_baseN");}
            }
            else {throw std::invalid_argument("Invalid number_baseN");}
        }
    }
    do 
    {
        curr = temp % M;
        result = curr > 9? char(curr+55)+result : std::to_string(curr) + result;
        temp = temp/M;
    }while (temp > 0); 
    return result;}
;
std::string BaseN::twoComplement(const std::string& in, int size)
{
    int size_in = in.size();
    if (size_in > size) {throw std::invalid_argument("Invalid input size");}
    std::string temp;
    for (size_t i = 0; i < in.size(); i++)
    {
        if (in[i] != '1' && in[i] != '0') {throw std::invalid_argument("Invalid input");}
        else  if(in[i] == '0') 
        {
            temp += '1';
        }
        else
        {
            temp += '0';
        }
;
    }
    for (int i = temp.size()-1; i >= 0; i--)
    {
        if (temp[i]=='0')
        {
            temp[i] = '1';
            break;
        }
        else 
            temp[i] = '0';
    }
    char last_char = temp[0];
    std::string result; 
    for(size_t i = 0; i < size-in.size();i++) {result+=last_char;}
    result = result + temp; 
    return result;
};
bool BaseN::isNegativeNumberBase2(const std::string& in, int size) 
{
    if (in.size() > size) {throw std::invalid_argument("Invalid input size");}
    for (size_t i = 0; i < in.size();i++) 
    {
        if (in[i] != '1' && in[i] != '0') {throw std::invalid_argument("Invalid input");}
    }
    if (in.size() == size && in[0]=='1') {return true;} 
    else {return false;}
}

std::string BaseN::add(const std::string& a, const std::string& b, int baseN){return"";};