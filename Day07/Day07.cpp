#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm> // for max_element(), min_element()
#include <stdlib.h> // abs()

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

ULL least_fuel_configuration(vector<ULL> positions, bool part_two){
    // because using infinity in C++ can be risky :)
    // this sets it to the max value this type of variable can have
    ULL least_fuel = numeric_limits<ULL>::max();
    int max = *max_element(positions.begin(), positions.end());
    int min = *min_element(positions.begin(), positions.end());

    for(int i = min; i<max+1; i++){
        ULL current_fuel = 0;
        for(int position : positions){
            // abs(int) ; position is ot type ULL; so we typecast
            ULL difference = abs(i - position);

            if(part_two==true){
                current_fuel += (ULL) difference*(difference+1)/2;
            }
            else{
                current_fuel += difference;
            }
        }
        if(current_fuel < least_fuel){
            least_fuel = current_fuel;
        }
    }

    return (ULL)least_fuel;
}

int main() {
   vector<ULL> crab_position = readFile("input.txt");

   // Part 1
   cout<<least_fuel_configuration(crab_position, false)<<endl;// 347449
   
   // Part 2
   cout<<least_fuel_configuration(crab_position, true)<<endl;// 98039527

    return 0;
}