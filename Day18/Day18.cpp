#include <iostream>
#include <fstream>
#include <vector>
#include <string>

typedef int ULLI;

using namespace std;

vector<ULLI> readFile(string filename){
    vector<ULLI> file_output;
    string line;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            cout<<line<<endl;
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return file_output;
}

void add(){
}

void explode(){
}

void split(){
}

int main() {
    vector<ULLI> blowfish_numbers = readFile("input.txt");

    return 0;
}
