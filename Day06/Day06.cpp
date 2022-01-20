#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm> // for rotate()

using ULL = unsigned long long ;

using namespace std;

vector<ULL> readFile(string filename){
    string line;
    ifstream myfile (filename);
    vector<ULL> i_fish(9);

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            stringstream ss(line);
            while(ss.good()){
                string substr;
                getline(ss, substr, ',');
                i_fish[stoull(substr)]++;
            }
        }
    }
    else{
        cout << "Unable to open file";
    }    
    
    return i_fish;
}

void printStructure(vector<ULL> v){
    for (auto itr : v) {
        cout << itr <<", ";
    }
    cout<<endl;
}

ULL addElements(vector<ULL> v){
    ULL sum = 0;
    for(auto element : v){
        sum+=element;
    }

    return sum;
}

ULL grow(vector<ULL> fishes, int max_days ){
    ULL sum = 0;
    for(int i = 0; i<max_days; i++){
        // instead of fishes.append(fishes.pop(0))
        // we rotate the vector to the left by 1 index
        rotate( fishes.begin(), fishes.begin() + 1, fishes.end() );
        fishes[6] += fishes[8];
    }

    return addElements(fishes);
}

int main() {
    vector<ULL> i_fish = readFile("input.txt");
    vector<ULL> i_fish2(i_fish);

    // Part 1
    cout<<grow(i_fish, 80)<<endl; // 343441

    // Part 2
    cout<<grow(i_fish2, 256)<<endl; // 1569108373832

    return 0;
}
