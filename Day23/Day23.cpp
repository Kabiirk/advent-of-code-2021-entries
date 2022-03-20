#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <array>
#include <list>
#include <assert.h>
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

class Burrow{
    public:
    array<char, 11> hallway;
    array< array<char, 2>, 4 > rooms;
    map<char, int> move_cost = {
        {'A',1},
        {'B',10},
        {'C',100},
        {'D',1000},
    };

    Burrow(array<char, 11> h, array< array<char, 2>, 4 > r){
        hallway = h;
        rooms = r;
    }

    void printBurrow(){
        cout<<" #############"<<endl;
        cout<<" #";
        for(unsigned i = 0; i < hallway.size(); i++){
            cout<<hallway[i];
        }
        Print("#");
        printf(" ###%c#%c#%c#%c###\n", rooms[0][0], rooms[1][0], rooms[2][0], rooms[3][0]);
        for(unsigned i = 1; i < rooms[0].size(); ++i){
            printf("   #%c#%c#%c#%c#\n", rooms[0][i], rooms[1][i], rooms[2][i], rooms[3][i]);
        }
        printf("   #########\n\n");
    }

    bool isClear(char c){
        return c=='.';
    }

    bool isAmphipod(char c){
        return c>='A' && c<='D';
    }

    unsigned targetRoom(char amphipod){
        return amphipod - 'A';
    }

    int outsideDoor(int r){
        int end_sz = (hallway.size() - (2*rooms.size()-1) )/2;
        return 2*r+end_sz;
    }

    bool allCozy(int r){
        char amphipod = 'A'+r;
        for(int i = 0; i<rooms[r].size(); i++){
            if(!isClear(rooms[r][i]) && rooms[r][i]!=amphipod){
                return false;
            }
        }
        
        return true;
    }

    bool isForbidden(int h){
        for(int i=0; i<rooms.size(); i++){
            if(outsideDoor(i)==h){
                return true;
            }
        }

        return false;
    }

    list<pair<Burrow, int>> moveOut(){
        list<pair<Burrow, int>> result;
        for(int r=0; r<rooms.size(); r++){
            if(allCozy(r)){
                continue;
            }

            int i = 0;
            while(i<rooms[r].size() && isClear(rooms[r][i])){
                i++;
            }
            if(i>=rooms[r].size()){
                continue;
            }
            char amphipod = rooms[r][i];
            assert(isAmphipod(amphipod));

            // move into hall
            int steps = i+1;
            int hall_pos = outsideDoor(r);
            assert(isClear(hallway[hall_pos]));

            // Walk left or right
            for(int dir : {-1, +1}){
                int h = hall_pos+dir;
                int s = steps+1;
                while(h>=0 && h<int(hallway.size())){
                    if(!isClear(hallway[h])){
                        // someone is in the way
                        break;
                    }
                    if(!isForbidden(h)){
                        Burrow next(*this);
                        next.rooms[r][i] = '.';
                        next.hallway[h] = amphipod;
                        result.emplace_back(next, s*move_cost[amphipod]);
                    }
                    h+=dir;
                    s++;
                }
            }
        }

        return result;
    }

    list<pair<Burrow, int>> moveIn(){
        list<pair<Burrow, int>> result;
        for (unsigned h = 0; h < hallway.size(); ++h){
            if (isClear(hallway[h])){
                continue;
            }
            char amphipod = hallway[h];
            // Room the amphipod wants
            unsigned r = targetRoom(amphipod);
            // Room must be empty or only have the same amphipod
            if (!allCozy(r)){
                continue;
            }
            // Check the steps along the hallway
            unsigned hr = outsideDoor(r);
            assert(h != hr);
            int dir = h < hr ? +1 : -1;
            unsigned hc = h + dir;
            unsigned steps = 1;
            while (hc != hr && isClear(hallway[hc])){
                hc += dir;
                ++steps;
            }
            if (!isClear(hallway[hc])){
                // Hallway blocked
                continue;
            }
            // Move in
            unsigned i = 0;
            ++steps;
            // All the way down
            while (i + 1 < rooms[r].size() && isClear(rooms[r][i + 1])) {
                i++;
                steps++;
            }
            Burrow next(*this);
            next.hallway[h] = '.';
            next.rooms[r][i] = amphipod;
            result.emplace_back(next, steps*move_cost[amphipod]);
        }

        return result;
    }

    list<pair<Burrow, int>> successor(){
        auto new_state = moveIn();
        if(!new_state.empty()){
            return new_state;
        }

        return moveOut();
    }

    bool allHome(){
        for(auto c  : hallway){
            if(!isClear(c)){
                return false;
            }
        }

        for(int r=0; r<rooms.size(); r++){
            if(!allCozy(r)){
                return false;
            }
        }

        return true;
    }
};

bool operator<(Burrow& b1, Burrow& b2){
    if(b1.hallway < b2.hallway){
        return true;
    }
    if(b2.hallway < b1.hallway){
        return false;
    }

    return b1.rooms < b2.rooms;
}

int main() {
    // readFile("input.txt");

    // Part 1// 14346
    /* Input :
    #############
    #...........#
    ###D#A#C#D###
      #C#A#B#B#
      #########
    */
    array<char, 11> hallway = { '.','.','.','.','.','.','.','.','.','.', '.' };
    // 2x brace because:
    // std::array<T, N> is an aggregate that contains a C array.
    // To initialize it, you need outer braces for the class
    // itself and inner braces for the C array
    array< array<char, 2>, 4 > rooms = {{
        {{'D','C'}},
        {{'A','A'}},
        {{'C','B'}},
        {{'D','B'}}
    }};
    Burrow b(hallway, rooms);
    b.printBurrow();

    // Part 2// 48984
    /* Input :
    #############
    #...........#
    ###D#A#C#D###
      #D#C#B#A#
      #D#B#A#C#
      #C#A#B#B#
      #########
    */

    return 0;
}
