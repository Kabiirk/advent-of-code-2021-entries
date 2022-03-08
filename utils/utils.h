#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <deque>

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
// #include <string>
#include <cstdlib>


typedef unsigned long long int ULLI;
typedef unsigned long long ULL;
typedef unsigned long UL;


// #######################################################################
// Miscellaneous Methods
// #######################################################################
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


template <typename B>
void printDeque(std::deque<B> dq){
    std::cout<<"[ ";
    for(auto it : dq){
        std::cout<<it<<" ";
    }
    std::cout<<"]"<<std::endl;
}

bool isLowerString(std::string s) {
    bool is_lower = true;

    for(char it : s){
        if(isupper(int(it))){
            return false;
        } 
    }
}

template <typename X>
void Print(X something, bool new_line=true){
    if(new_line){
        std::cout<<something<<std::endl;
    }
    else{
        std::cout<<something;
    }
}

// #######################################################################
// Pair Related Methods
// #######################################################################
template <typename A, typename B>
void printPair(std::pair<A,B> p){
    std::cout<<"("<<p.first<<","<<p.second<<") ";
    std::cout<<std::endl;
}

// #######################################################################
// Vector Related Methods
// #######################################################################
template <typename A>
bool ElementIn(const A s, std::vector<A> vec){
    /*
    Determines whether a string or integer is present in vector<string>
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

template <typename B>
std::vector<std::pair<int, B>> vecEnumerate(std::vector<B> vec, int start=0){
    int i = start;
    std::vector<std::pair<int, B>> v;
    for(auto it : vec){
        v.push_back(make_pair(i, it));
        i++;
    }

    return v;
}

int sumOfVecElements(std::vector<int> vec){
    /*
    Returns sum(type int) of all elements in a vector<int>
    */
    int sum = 0;
    for(auto i : vec){
        sum+=i;
    }

    return sum;
}

template <typename S>
S maxElement(std::vector<S> v){
    S max_elem = *max_element(v.begin(), v.end());

    return max_elem;
}

template <typename M>
M minElement(std::vector<M> v){
    M min_elem = *min_element(v.begin(), v.end());

    return min_elem;
}

template <typename T>
T printVector( std::vector<T> vec, bool newline=false){
    /*
    Prints vector of any type

    TODO :
        1. Ability to print vector having data-type like
           pairs etc.
        2. Print Multi-dimensional vectors
    */

    std::cout<<"< "<<std::endl;
    for(auto it : vec){
        if(newline){
            std::cout<<it<<std::endl;
        }
        else{
            std::cout<<it<<" ";
        }
    }
    std::cout<<">";
    std::cout<<std::endl;
}

template <typename A>
void print2DVec(std::vector<std::vector<A>> vec){
    for(auto row : vec){
        printVector(row);
    }
}

template <typename S, typename T>
void printVecPair(std::vector<std::pair<S, T>> vec){
    std::cout<<"< ";
    for(auto i : vec){
        std::cout<<"("<<i.first<<","<<i.second<<") ";
    }
    std::cout<<">"<<std::endl;
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

std::string joinVecAsString(std::vector<int> v){
    std::string s;
    for(auto a : v){
        s+=std::to_string(a);
    }
    return s;
}

// #######################################################################
// Map Related Methods
// #######################################################################
template <typename I, typename J>
void printMap(std::map<I,J> m){
    std::cout<<"{ ";
    for(auto it = m.begin(); it != m.end(); ++it){
        std::cout<<it->first <<":"<<it->second<<"; ";
    }
    std::cout<<"}"<<std::endl;
}


// #######################################################################
// Set Related Methods
// #######################################################################
std::set<std::string> stringToSet(std::string str){
    /*
    Takes a string and returns a set of distinct characters in the string.

    E.g. : stringToSet("Hello") returns :
           set s = { "H", "e", "l", "o" }
    */
    std::set<std::string> str_set;
    for(char s : str){
        str_set.insert(std::string{s});
    }

    return str_set;
}

template <class A>
bool isSubset(std::set<A> s1, std::set<A> s2){
    /*
    Checks if s2 is a subset of s1
        * Returns True if s2 is a subset of s1
        * Returns False Otherwise
    */
    if(std::includes(s1.begin(), s1.end(), s2.begin(), s2.end())){
        return true;
    }
    return false;
}

template <typename I, typename J>
void printSetPair(std::set<std::pair<I, J>> s){
    std::cout<<"{ ";
    for(auto itr : s){
        std::cout<<"("<<itr.first<<","<<itr.second<<") ";
    }
    std::cout<<"}"<<std::endl;
}

template <typename K>
void printSet(std::set<K> s){
    std::cout<<"{ ";
    for(auto a : s){
        std::cout<<a<<", ";
    }
    std::cout<<"}"<<std::endl;
}