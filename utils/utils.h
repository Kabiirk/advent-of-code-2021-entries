#include <iostream>
#include <vector>


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