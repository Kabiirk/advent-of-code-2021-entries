#include <iostream>
#include <fstream>
#include <string>

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
    cout<<"Hello World!"<<endl;
    readFile("input.txt");

    return 0;
}