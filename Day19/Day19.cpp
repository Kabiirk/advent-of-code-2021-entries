#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void readFile(string filename){
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

}

int main() {
    readFile("input.txt");

    return 0;
}
