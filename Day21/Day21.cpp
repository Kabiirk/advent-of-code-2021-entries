#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

using namespace std;

pair<int, int> readFile(string filename){
    ifstream myfile (filename);
    int player_1=0, player_2=0;

    if (myfile.is_open())
    {
        string line;
        while ( getline(myfile, line) )
        {
            // Player 1 starting position: 4
            const regex r("Player (-?\\d*) starting position: (-?\\d*)");  
            smatch result;

            // can't add numbers to a pair iteratively
            // result = ["Player 1 starting position: 4", "1", "4"]
            if (regex_search(line, result, r)) {
                if(result[1]=='1'){
                    player_1 = stoi(result[2]);
                }
                else{
                    player_2 = stoi(result[2]);
                }
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return make_pair(player_1, player_2);
}

// Helper function for both parts
uint32_t getMod(uint32_t value, uint32_t max){
    return (value-1)%max + 1;
}

// For Part 1
template <uint32_t sides> uint32_t dice(){
    static uint32_t value = 0;
    return value = getMod(value+1, sides);
}

uint32_t simulateTurns(uint32_t position){
    return getMod(position+dice<100>()+dice<100>()+dice<100>(), 10);
}

uint32_t part1(pair<int, int> player_positions, bool verbose=false){
    uint32_t p1_pos = player_positions.first;
    uint32_t p2_pos = player_positions.second;
    uint32_t p1_score=0, p2_score=0, rolls=0;

    while(true){
        // Player 1
        p1_pos = simulateTurns(p1_pos);
        p1_score += p1_pos;
        rolls+=3;
        if(p1_score >= 1000){
            if(verbose){
                cout<<"Player 1 Won with : "<<p1_score<<endl;
                cout<<"Player 2 Lost with : "<< p2_score <<endl;
                cout<<"Dice was rolled : "<<rolls<<" times."<<endl;
            }
            return rolls*p2_score;
        }
        
        // Player 2
        p2_pos = simulateTurns(p2_pos);
        p2_score += p2_pos;
        rolls+=3;
        if(p2_score >= 1000){
            if(verbose){
                cout<<"Player 2 Won with : "<<p2_score<<endl;
                cout<<"Player 1 Lost with : "<< p1_score <<endl;
                cout<<"Dice was rolled : "<<rolls<<" times."<<endl;
            }
            return rolls*p1_score;
        }
    }
}

// For Part 2
// TODO : Speed it up with cache ? This may be re-calculating some states
//        use a map< State : Score > to store calculated states and their score
unordered_map<uint32_t, uint32_t> distribution = {{3, 1}, {4, 3}, {5, 6}, {6, 7}, {7, 6}, {8, 3}, {9, 1}};

pair<uint64_t, uint64_t> countWins(uint64_t player1_score, uint64_t player2_score, uint64_t player1_pos, uint64_t player2_pos, bool player1_turn) {
    if (player1_turn){
        if (player2_score >= 21)
            return {0, 1};
        if (player1_score >= 21)
            throw runtime_error("Inconsistency.");
    } 
    else{
        if (player1_score >= 21)
            return {1, 0};
        if (player2_score >= 21)
            throw runtime_error("Inconsistency.");
    }

    if (player1_turn){
        pair<uint64_t, uint64_t> sum = {0, 0};
        for (auto rc : distribution){
            auto roll = rc.first;
            auto cnt = rc.second;
            uint64_t new_pos = getMod(player1_pos + roll, 10);
            auto tp = countWins(player1_score + new_pos, player2_score, new_pos, player2_pos, false);
            sum.first += cnt * tp.first;
            sum.second += cnt * tp.second;
        }
        return sum;
    }
    else{
        pair<uint64_t, uint64_t> sum = {0, 0};
        for (auto rc : distribution){
            auto roll = rc.first;
            auto cnt = rc.second;
            uint64_t new_pos = getMod(player2_pos + roll, 10);
            auto tp = countWins(player1_score, player2_score + new_pos, player1_pos, new_pos, true);
            sum.first += cnt * tp.first;
            sum.second += cnt * tp.second;
        }
        return sum;
    }
}

uint64_t greaterElement(pair<uint64_t, uint64_t> p){
    return (p.first>p.second) ? p.first : p.second;
}

int main() {
    pair<int, int> player_positions = readFile("input.txt");

    // Part 1
    // cout<<part1(player_positions, true)<<endl;// 855624
    cout<<part1(player_positions)<<endl;// 855624

    // Part 2
    pair<uint64_t, uint64_t> p2 = countWins(0,0,player_positions.first, player_positions.second, true);
    cout<< greaterElement(p2) <<endl;// 187451244607486

    return 0;
}