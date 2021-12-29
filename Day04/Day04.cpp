#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void readFile(string filename){
    string line;
    ifstream myfile (filename);
    int blank = 0;

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            //cout<<line<<endl;
            if(line.length() == 0){
                //cout<<"blank !"<<endl;
                blank++;
            }
            else{
                cout<<line<<endl;
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    cout<<blank;

    //return report;
}

class Board{
    private:
        int hello = 0;

    public:
        void setHello(int n){
            hello = n;
        }
    
        void getHello(){
            cout<<hello<<endl;
        }
};

int main() {
    readFile("input.txt");

    return 0;
}
