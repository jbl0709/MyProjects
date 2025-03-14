#include <iostream> 
#include "BaseN.hpp"

int main(int argc, const char* argv[])
{
    if (argc < 4) 
    {
        std::cout << argv[0] << "missing input arguments atleast 4"<<std::endl;
        return 1; 

    }
    std::string first_argument = argv[1];
    if ( first_argument == "a") 
    {
        BaseN basenaufgabe;
        int n = std::stoi(argv[3]);
        int m = std::stoi(argv[4]);
        std::string result = basenaufgabe.convert(argv[2],n,m);
        std::cout << "Converting: '" << argv[2] << "' (base "<<n<<")" << "--> '" <<result<< "' (base "<<m<<")";
    }
    if (first_argument == "b") 
    {
        BaseN basenaufgabe; 
        int size = std::stoi(argv[3]);
        std::string zahl = basenaufgabe.convert(argv[2],2,10);
        std::string result = basenaufgabe.twoComplement(argv[2],size);
        std::cout << "Two Complement: '"<<argv[2]<<"' (=="<<zahl<<")"<< " --> '" << result << "' (==-"<<zahl<<")";
        
    }
    if (first_argument == "c")
    {
        std::cout << "Bonusaufgabe wurde nicht gemacht.";
    }
    return 0;
}