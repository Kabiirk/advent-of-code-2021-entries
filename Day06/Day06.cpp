#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

vector<int> readFile(string filename){
    vector<int> initial_fish;
    string line;
    ifstream myfile (filename);

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            stringstream ss(line);
            while(ss.good()){
                string substr;
                getline(ss, substr, ',');
                initial_fish.push_back(stoi(substr));
            }
        }
    }
    else{
        cout << "Unable to open file";
    }    
    
    return initial_fish;
}

int main() {
    vector<int> initial_fish = readFile("input.txt");
    

    return 0;
}
