#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;


/*
<
< nums >,
< <r><c> >
>
*/
void readFile(string filename){
    vector<string> full_data;
    vector<int> line_data;
    int linecount = 1;
    string line;
    ifstream myfile (filename);
    int blank = 0;

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            if(line.length() == 0){
                //cout<<"blank !"<<endl;
                blank++;
            }
            else{
                const regex r("(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)");
                smatch result;
                if(regex_search(line, result, r)){
                    //cout<<line<<endl;
                    cout<<result[1]<<"->"<<result[3]<<"->"<<result[5]<<"->"<<result[7]<<"->"<<result[9]<<endl;
                }
                // if(linecount == 1){
                //     //stringstream ss (line);
                //     cout<<"Top Line !!"<<endl;
                //     linecount++;
                // }
                // else{
                //     stringstream ss (line);
                //     cout<<line<<endl;
                // }
                //full_data.push_back(line);
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

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
