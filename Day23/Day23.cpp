#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "../utils/utils.h"

using namespace std;
/*
Part 2 input
#############
#...........#
###D#A#C#D###
  #D#C#B#A#
  #D#B#A#C#
  #C#A#B#B#
  #########
*/

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

int checkState(){
    

    return 0;
}

int main() {
    readFile("input.txt");

    // Part 1// 14346

    // Part 2// 48984

    return 0;
}
