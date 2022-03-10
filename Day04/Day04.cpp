#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include "../utils/utils.h"

using namespace std;

using BOARD = vector< vector<int> >;
using BOARDBOOL = vector< vector<bool> >;

class Board{
    public:
        // Contructor
        explicit Board(BOARD board){
            numbers = board;
        };

    bool hasWon(){
        for(int row=0; row<5; row++){
            if(winningRow(row)){
                return true;
            }
        }

        for(int col=0; col<5; col++){
            if(winningCol(col)){
                return true;
            }
        }

        return false;
    }

    void mark(const int num){
        for(int row=0; row<5; row++){
            for(int col=0; col<5; col++){
                if(num == numbers[row][col]){
                    marked[row][col] = true;
                }
            }
        }
    }

    int score(const int called_number){
        int unmarked_sum = 0;
        for(int row=0; row<5; row++){
            for(int col=0; col<5; col++){
                if(!marked[row][col]){
                    unmarked_sum  += numbers[row][col];
                }
            }
        }

        return unmarked_sum * called_number;
    }

    private:
        bool winningRow(int row){
            // std::count
            return count(marked[row].begin(), marked[row].end(), true) == 5;
        }

        bool winningCol(int col){
            for(int row=0; row<5; row++){
                if(!marked[row][col]){
                    return false;
                }
            }
            return true;
        }
        BOARD numbers;
        // The below initialization isn't working :(
        // BOARDBOOL marked(5, vector<bool>( 5, false ) );
        BOARDBOOL marked = {
            {false,false,false,false,false},
            {false,false,false,false,false},
            {false,false,false,false,false},
            {false,false,false,false,false},
            {false,false,false,false,false},
        };
};

struct ReqData{
    vector<int> nums;
    vector<Board> boards;
};

ReqData readFile(string filename){
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
    ReqData req_data;
    string line;
    ifstream myfile (filename);

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            if(line.length() == 0){
                continue;
            }
            else if(line.length() > 14){
                stringstream ss(line);

                while(ss.good()){
                    string substr;
                    getline(ss, substr, ',');
                    req_data.nums.push_back(stoi(substr));
                }
            }
            else{
                const regex r("(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)(\\s*)(\\d*)");
                smatch result;
                if(regex_search(line, result, r)){
                    vector<int> line_data{ stoi(result[2]), stoi(result[4]), stoi(result[6]), stoi(result[8]), stoi(result[10]) };
                    full_data.push_back(line_data);
                    // Best practice to clear vector AND de-allocate memory
                    // Ref. : https://www.techiedelight.com/delete-vector-free-memory-cpp/
                    // vector<int>().swap(line_data);
                }
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    // Re-arranging full_data into Desired vector of Board class
    int track = 0;

    while( full_data.size() > 0 ){
        BOARD current_board;
        while(track < 5){
            vector<int> current_line;
            current_line = *full_data.begin();
            current_board.push_back(current_line);
            // operation similar to pop_front() for vectors
            full_data.erase(full_data.begin());
            track++;
        }
        track = 0;

        Board board(current_board);
        req_data.boards.push_back(board);
    }

    return req_data;
}

int solve(ReqData data, bool part_2=false){
    // Part 1
    if(!part_2){
        for(auto call : data.nums){
            for(auto& board : data.boards){
                board.mark(call);
                if(board.hasWon()){
                    return board.score(call);
                }
            }
        }
    }
    // Part 2
    else{
        for(auto call : data.nums){
            vector<Board> remaining_boards;
            for(auto& board : data.boards){
                board.mark(call);
                if(!board.hasWon()){
                    remaining_boards.push_back(board);
                }
                else if(data.boards.size() == 1){
                    return board.score(call);
                }
            }
            data.boards = move(remaining_boards);
        }
    }
}


int main(){
    ReqData data = readFile("input.txt");

    // Part 1
    cout<<solve(data)<<endl;// 14093

    // Part 2
    cout<<solve(data, true)<<endl;// 17388

    return 0;
}