#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "utils.h"

int main(){
    // Testing printVector()
    vector<int> i = {1,2,3,4,5};
    vector<string> s = {"1","2","3","4","7"};
    printVector(i);
    printVector(s);

    // Testing SplitToVecXXX() functions
    string a1 = "1,2,3,4,7,8";
    vector<unsigned long long> a = splitToVectorULL(a1);
    vector<unsigned long> b = splitToVectorUL(a1);
    vector<long> c = splitToVectorLong(a1);
    printVector(a);
    printVector(b);
    printVector(c);

    // Testing printMap()
    map<string, int> m = {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}};
    printMap(m);

    return 0;
}