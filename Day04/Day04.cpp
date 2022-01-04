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
    vector<vector<int>> full_data;
    vector<int> line_data;
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
                const regex r("(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)");
                smatch result;
                if(regex_search(line, result, r)){
                    //cout<<line<<endl;
                    //cout<<result[1]<<"->"<<result[3]<<"->"<<result[5]<<"->"<<result[7]<<"->"<<result[9]<<endl;
                    // TODO : Find a faster way to do this
                    line_data.push_back(stoi(result[2]));
                    line_data.push_back(stoi(result[4]));
                    line_data.push_back(stoi(result[6]));
                    line_data.push_back(stoi(result[8]));
                    line_data.push_back(stoi(result[10]));
                    full_data.push_back(line_data);
                    // Best practice to clear vector AND de-allocate memory
                    // Ref. : https://www.techiedelight.com/delete-vector-free-memory-cpp/
                    // line_data.resize(0);
                    // line_data.shrink_to_fit();
                    vector<int>().swap(line_data);
                }
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    // Re-arranging the full_data to desired shape
    vector< vector< vector<int> > > board = { { { 1,2,3,4,5}, { 1,2,3,4,5}} };

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
