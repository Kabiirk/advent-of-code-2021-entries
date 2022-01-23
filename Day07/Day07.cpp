#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

typedef unsigned long long ULL;

using namespace std;

vector<ULL> readFile(string filename){
    string line;
    ifstream myfile (filename);
    vector<ULL> crab_position;

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            stringstream ss(line);
            while(ss.good()){
                string substr;
                getline(ss, substr, ',');
                crab_position.push_back(stoull(substr));
            }
        }
    }
    else{
        cout << "Unable to open file";
    }    
    
    return crab_position;
}

int main() {
   vector<ULL> crab_position = readFile("input.txt");
   cout<<crab_position[0]<<endl;

    return 0;
}
