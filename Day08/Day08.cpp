#include <iostream>
#include <fstream>
#include <string>
#include "../utils/utils.h"

using namespace std;

void readFile(string filename){
    string line;
    ifstream myfile (filename);

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            cout<<line<<endl;
        }
    }
    else cout << "Unable to open file";
}

int main() {
    //readFile("input.txt");
    vector<int> i = {1,2,3,4,5};
    vector<string> s = {"1","2","3","4","7"};

    printVector(i);
    printVector(s);
    return 0;
}