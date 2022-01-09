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

    public:
        // Constructor
        Board( vector<vector<int>> board ){

            // for testing
            // for(auto row : board){
            //     for(auto col : row){
            //         cout<<col<<" ";
            //     }
            //     cout<<endl;
            // }
            // cout<<endl;
            int height = board.size();
            int width = board[0].size();

            for(int i=0; i<width; i++){
                this->col_hits.push_back(height);
            }

            for(int j=0; j<height; j++){
                this->row_hits.push_back(width);
            }

            for(int y = 0; y<board.size();y++ ){
                for(int x = 0; x<board[y].size(); x++){
                    this->nums[board[y][x]] = make_tuple(x, y);
                }
            }

            this->has_bingo = false;
        }

        void call(int num){
            tuple<int, int> position = this->nums[num];
            this->nums.erase(num);

            cout<<endl;
            
            int x = get<0>(position);
            int y = get<1>(position);

            this->col_hits[x]-=1;
            this->row_hits[y]-=1;
            
            this->has_bingo = this->has_bingo || (!this->col_hits[x]) || (!this->row_hits[y]);
        }

        int unmarkedSum(){
            int sum = 0;
            for(map<int, tuple<int, int>>::iterator it = this->nums.begin(); it != this->nums.end(); it++){
                sum+=it->first;
            }

            return sum;
        }

        // Static Methods
        // static Board toClassObject( vector<vector<int>> board ){
        //     return Board(board);
        // }
};

tuple<int, int> solve( vector<int> nums, vector<Board> boards ){
    set<int> won;
    vector<int> wins;
    for(auto num : nums){
        for(int j = 0; j<boards.size(); j++){
            cout<<"{ ";
            for( map<int, tuple<int,int> >::const_iterator it = boards[j].nums.begin();it != boards[j].nums.end(); ++it){
                int a = get<0>(it->second);
                int b = get<1>(it->second);
                cout<<it->first<<": "<<"("<<a<<", "<<b<<"), ";
            }
            cout<<" }"<<endl;
            bool is_in_win = won.find(j) != won.end();
            if(is_in_win){
                continue;
            }
            
            boards[j].call(num);
            if(boards[j].has_bingo){
                won.insert(j);
                wins.push_back(num*boards[j].unmarkedSum());
            }
        }
    }
    return make_tuple(wins[0],wins[wins.size()-1]);
}

int main() {
    auto data = readFile("input.txt");
    vector<int> nums = get<0>(data);
    vector<vector<vector<int>>> boards = get<1>(data);
    // Find way to better use the memory
    vector<Board> B;
    vector<Board> C;

    for(int i = 0; i<boards.size(); i++){
        Board b(boards[i]);
        B.push_back(b);
    }

    C.push_back(B[99]);
    tuple<int, int> result = solve(nums, C);
    cout<<get<0>(result)<<endl;
    cout<<get<1>(result)<<endl;
    //Board C(boards[0]);
    return 0;
}