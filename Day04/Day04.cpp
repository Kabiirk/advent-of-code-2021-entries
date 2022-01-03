#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

using namespace std;


/*
< nums >
<
    < <Board 1 row 1>, <Board 1 Row 2> ... <Board 1 Row 5> >,
    < <Board 2 row 1>, <Board 2 Row 2> ... <Board 2 Row 5> >,
    < <Board 3 row 1>, <Board 3 Row 2> ... <Board 3 Row 5> >,
    .....
    < <Board n row 1>, <Board n Row 2> ... <Board n Row 5> >,
>
*/
void readFile(string filename){
    vector<string> full_data;
    vector<int> line_data;
    int linecount = 1;
    int rowcount = 0;
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
            else if(line.length() > 14){
                blank++;
            }
            else{
                const regex r("(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)");
                smatch result;
                if(regex_search(line, result, r)){
                    //cout<<line<<endl;
                    if(rowcount<=4)
                    {
                        cout<<result[1]<<"->"<<result[3]<<"->"<<result[5]<<"->"<<result[7]<<"->"<<result[9]<<endl;
                        rowcount++;
                    }
                    else{
                        cout<<endl;
                        rowcount = 0;
                    }
                }
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
