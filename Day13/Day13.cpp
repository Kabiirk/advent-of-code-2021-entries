#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <regex>

using namespace std;

using DOTS = set<pair<int, int>>;
using INSTRUCTION = vector<pair<string, int>>;

struct RequiredData{
    DOTS dot_set;
    INSTRUCTION instructions_vec;
};

RequiredData readFile(string filename){
    string line;
    ifstream myfile (filename);
    RequiredData req_data;

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            // Coordinates
            if(isdigit(line[0])){
                const regex r("(-?\\d*),(-?\\d*)");
                smatch result2;
                // result2 = ["994,18", "994", "18"]
                if (regex_search(line, result2, r)){
                    req_data.dot_set.insert(make_pair( stoi(result2[1]), stoi(result2[2]) ) );
                }
            }
            // Fold Instructions
            else if(line[0]=='f'){
                const regex r("fold along (\\w)=(-?\\d*)");
                smatch result;
                // result = ["fold along x=655", "x", "655"]
                if (regex_search(line, result, r)){
                    req_data.instructions_vec.push_back(make_pair(result[1], stoi(result[2])));
                }
            }
        }
    }
    else cout << "Unable to open file";

    return req_data;
}

DOTS fold(DOTS coord_set, pair<string, int> instruction){
    string axis = instruction.first;
    int fold_value = instruction.second;
    DOTS new_dot_set;

    for(auto this_coord : coord_set){
        int x = this_coord.first;
        int y = this_coord.second;
        if(axis == "x"){
            // Vertical folding action 
            // If x is bigger than the fold, it's value will change
            // The formula for how it will change is 2 * fold_value - x
            
            // If x is smaller, no change, but add to new set
            // because of inward folding
            if(x>fold_value){
                new_dot_set.insert( make_pair( 2*fold_value-x, y ) );
            }
            else{
                new_dot_set.insert( make_pair( x,y ) );
            }
        }
        else{
            // axis == 'y' i.e. Horizontal folding action
            // Same as above, but for y now.
            if(y>fold_value){
                new_dot_set.insert( make_pair( x,2*fold_value-y ) );
            }
            else{
                new_dot_set.insert( make_pair( x,y ) );
            }
        }
    }

    return new_dot_set;
}

pair<int, int> findDimensionofCanvas(DOTS dots){
    int max_x = 0;
    int max_y = 0;
    for(auto dot : dots){
        int x = dot.first;
        int y = dot.second;
        if(x > max_x){
            max_x = x;
        }
        if(y>max_y){
            max_y = y;
        }
    }

    return make_pair(max_x, max_y);
}

int main() {
    RequiredData req_data =  readFile("input.txt");
    DOTS dots = req_data.dot_set;
    INSTRUCTION instructions = req_data.instructions_vec;

    // Part 1
    DOTS first_fold = fold(dots, instructions[0]);
    cout<<first_fold.size()<<endl;// 763

    // Part 2 
    // Let the folding begin ! 
    for(auto instruction : instructions){
        dots = fold(dots, instruction);
    }
    pair<int, int> max_dimension = findDimensionofCanvas(dots);
    int max_x = max_dimension.first;// 38
    int max_y = max_dimension.second;// 5

    // Display output by 'drawing' final folded sheet
    for(int y = 0; y<max_y+1; y++){
        string output="";
        for(int x = 0; x<max_x+1; x++){
            if(dots.find(make_pair(x,y)) != dots.end()){
                output+="#";
            }
            else{
                output+=" ";
            }
        }
        cout<<output<<endl;
    }
    // Answer : RHALRCRA
    // Output :
    // ###  #  #  ##  #    ###   ##  ###   ## 
    // #  # #  # #  # #    #  # #  # #  # #  #
    // #  # #### #  # #    #  # #    #  # #  #
    // ###  #  # #### #    ###  #    ###  ####
    // # #  #  # #  # #    # #  #  # # #  #  #
    // #  # #  # #  # #### #  #  ##  #  # #  #

    return 0;
}