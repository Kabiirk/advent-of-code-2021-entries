#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

#include "utils.h"

int main(){
    // Testing printVector()
    vector<int> i = {1,2,3,4,5,79};
    vector<string> s = {"1","2","3","4","7","element"};
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

    // Testing maxElement()
    cout<<maxElement(i)<<endl;

    // Testing sumOfVecElements()
    vector<int> i2 = {1,2,3,4,5,79};
    cout<<sumOfVecElements(i2)<<endl;

    // Testing printMap()
    map<string, int> m1 = {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}};
    printMap(m1);

    int x1;
    cout<< type_name<decltype(x1)>() <<endl;
    char x2;
    cout<< type_name<decltype(x2)>() <<endl;
    // works when these variables are printed individually
    // but causing segmentation fault when printing them all
    // together
    //
    // bool x3;
    // cout<< type_name<decltype(x3)>() <<endl;
    // float x4;
    // cout<< type_name<decltype(x4)>() <<endl;
    double x5;
    cout<< type_name<decltype(x5)>() <<endl;
    vector<int> x;
    cout<< type_name<decltype(x)>() <<endl;
    pair<int, int> p = {1, 2};
    cout<< type_name<decltype(p)>() <<endl;

    // Test StringIn()
    string to_find = "element";
    cout<<ElementIn(to_find, s)<<endl;
    cout<<ElementIn((string)"5", s)<<endl;
    cout<<ElementIn(5, i)<<endl;
    cout<<ElementIn(50, i)<<endl;

    vector<pair<int, string>> v = vecEnumerate(s);
    printVecPair(v);

    return 0;
}