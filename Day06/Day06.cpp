#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

typedef unsigned long long ULL;

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
                i_fish[stoull(substr)]+=1;
            }
        }
    }
    else{
        cout << "Unable to open file";
    }    
    
    return i_fish;
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
        // ~ fishes.pop(0)
        int front = *fishes.begin();
        fishes.erase(fishes.begin());

        fishes.push_back(front);
        fishes[6] += fishes.back();
    }

    return addElements(fishes);
}

void printStructure(vector<ULL> v){
    for (auto itr : v) {
        cout << itr <<", ";
    }
    cout<<endl;
}

int main() {
    //vector<int> initial_fish = readFile("input.txt");
    vector<ULL> i_fish = readFile("input.txt");
    vector<ULL> i_fish2(i_fish);
    cout<<grow(i_fish, 80)<<endl; // 343441
    cout<<grow(i_fish, 256)<<endl;
    // 1569108373832
    // 18446744062269960520

    // vector<int> v = {1,2,3,4,5,6,7};
    // cout<<*v.begin()<<endl;
    // printStructure(v);
    // v.push_back(*v.begin());
    // v.erase(v.begin());
    // printStructure(v);
    // cout<<*v.begin()<<endl;
    

    return 0;
}
