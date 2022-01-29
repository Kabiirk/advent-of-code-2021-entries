#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

typedef unsigned long long int ULLI;
typedef unsigned long long ULL;
typedef unsigned long UL;


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
    cout<<"{"<<endl;
    for(map<I,J>::const_iterator it = m.begin(); it != m.end(); ++it){
        std::cout<<it->first <<" : "<<it->second<<std::endl;
    }
    cout<<"}"<<endl;
}