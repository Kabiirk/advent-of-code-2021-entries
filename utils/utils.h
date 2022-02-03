#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

/*
for type()
Ref.: https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
*/
#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>


typedef unsigned long long int ULLI;
typedef unsigned long long ULL;
typedef unsigned long UL;

template <typename A>
bool ElementIn(const A s, std::vector<A> vec){
    /*
    Determins whether a string or integer is present in vector<string>
    or in a vector<int> respectively
        * Returns True if string is present in vector
        * Returns False Otherwise
    
    TODO :
        1. When comparing with strings like "1", "a", "element" when passing directly into funciton
           gives error "no instance of function template "ElementIn" matches the argument list -- argument types are: (const char [2], std::vector<std::string, std::allocator<std::string>>)"
           while writing ElementIn("1", string_vector ) so we have to do -> ElementIn((string)"1", string_vector) 
           Some reference for way forward : https://stackoverflow.com/questions/17111140/string-in-function-parameter
        2. Write Code to handle incorrect parameters (wrong vector, looking for int in vector<string> etc.)
    */
    if (std::find(vec.begin(), vec.end(), s) != vec.end())
    {
        return true;
    }
    return false;
}

template <typename T>
T printVector( std::vector<T> vec){
    /*
    Prints vector of any type
    
    TODO :
        1. Ability to print vector having data-type like 
           pairs etc.
        2. Print Multi-dimensional vectors
    */

    std::cout<<"< ";
    for(auto it : vec){
        std::cout<<it<<" ";
    }
    std::cout<<">";
    std::cout<<std::endl;
}


std::vector<ULL> splitToVectorULL(std::string line){
    int a = 0;
    std::vector<ULL> output_vector;
    std::stringstream ss(line);
    while(ss.good()){
        std::string substr;
        getline(ss, substr, ',');
        output_vector.push_back(stoull(substr));
    }

    return output_vector;
}


std::vector<UL> splitToVectorUL(std::string line){
    int a = 0;
    std::vector<UL> output_vector;
    std::stringstream ss(line);
    while(ss.good()){
        std::string substr;
        getline(ss, substr, ',');
        output_vector.push_back(stoul(substr));
    }

    return output_vector;
}


std::vector<long> splitToVectorLong(std::string line){
    int a = 0;
    std::vector<long> output_vector;
    std::stringstream ss(line);
    while(ss.good()){
        std::string substr;
        getline(ss, substr, ',');
        output_vector.push_back(stol(substr));
    }

    return output_vector;
}

template <typename I, typename J>
void printMap(std::map<I,J> m){
    std::cout<<"{"<<std::endl;
    for(auto it = m.begin(); it != m.end(); ++it){
        std::cout<<"    "<<it->first <<" : "<<it->second<<std::endl;
    }
    std::cout<<"}"<<std::endl;
}

template <class T>
std::string
type_name(){
    /*
    Prints type of variable
    TODO :
        1. Print Class type of object
    */

    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
           (
                #ifndef _MSC_VER
                    abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                           nullptr, nullptr),
                #else
                    nullptr,
                #endif
                    std::free
           );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";

    return r;
}