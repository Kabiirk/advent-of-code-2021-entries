#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <tuple>
#include <map>
#include <set>

using namespace std;

tuple< vector<int>, vector<vector<vector<int>>> > readFile(string filename){
    /*
    Desired Vector shapes :
    nums = < 1, 2, 3, 4 .... >

    boards = 
    <
        < <Board 1 row 1>, <Board 1 Row 2> ... <Board 1 Row 5> >,
        < <Board 2 row 1>, <Board 2 Row 2> ... <Board 2 Row 5> >,
        < <Board 3 row 1>, <Board 3 Row 2> ... <Board 3 Row 5> >,
        .....
        < <Board n row 1>, <Board n Row 2> ... <Board n Row 5> >,
    >
    */
    vector<vector<int>> full_data;
    vector<int> line_data;
    vector<int> nums;
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
                stringstream ss(line);

                while(ss.good()){
                    string substr;
                    getline(ss, substr, ',');
                    nums.push_back(stoi(substr));
                }
            }
            else{
                const regex r("(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)");
                smatch result;
                if(regex_search(line, result, r)){
                    //cout<<line<<endl;
                    //cout<<result[1]<<"->"<<result[3]<<"->"<<result[5]<<"->"<<result[7]<<"->"<<result[9]<<endl;
                    // TODO : Find a faster/better way to do this
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

    // Re-arranging full_data into Desired Vector shape
    vector< vector< vector<int> > > boards;
    int track = 0;

    while( full_data.size() > 0 ){
        vector<vector<int>> current_board;
        while(track < 5){
            vector<int> current_line;
            current_line = *full_data.begin();
            current_board.push_back(current_line);
            // operation similar to pop_front() for vectors
            full_data.erase(full_data.begin());
            track++;
        }
        track = 0;
        boards.push_back(current_board);
    }

    return make_tuple(nums, boards);
}

class Board{
    public:
        vector<int> col_hits, row_hits;
        bool has_bingo;
        map<int, tuple<int, int>> nums;

        // Constructor
        Board( vector<vector<int>> board ){
            int height = board.size();
            int width = board[0].size();

            for(int i=0; i<width; i++){
                this->col_hits.push_back(height);
            }
            for(int j=0; j<height; j++){
                this->col_hits.push_back(width);
            }

            for(int k = 0; k<board.size();k++ ){
                for(int l = 0; l<board[k].size(); l++){
                    this->nums[board[k][l]] = make_tuple(l, k);
                }
            }

            this->has_bingo = false;
        }

        void call(int num){
            tuple<int, int> position = this->nums[num];
            this->nums.erase(this->nums.find(num));
            int x = get<0>(position);
            int y = get<1>(position);

            this->col_hits[x]--;
            this->row_hits[y]--;
            this->has_bingo = this->has_bingo || !this->col_hits[x] || !this->row_hits[y];
        }

        int unmarkedSum(){
            int sum = 0;
            for(map<int, tuple<int, int>>::iterator it = this->nums.begin(); it != this->nums.end(); ++it){
                sum+=it->first;
            }

            return sum;
        }
};

tuple<int, int> solve( vector<int> nums, vector<vector<vector<int>>> boards ){
    set<int> won;
    vector<int> wins;
    int num;

    return make_tuple(1,2);
}

int main() {
    auto data = readFile("input.txt");
    vector<int> nums = get<0>(data);
    vector<vector<vector<int>>> boards = get<1>(data);
    
    return 0;
}