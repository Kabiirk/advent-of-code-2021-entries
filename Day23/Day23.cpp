#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <array>
#include <list>
#include <assert.h>
#include "../utils/utils.h"

using namespace std;

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
        for(int i = 0; i < hallway.size(); i++){
            cout<<hallway[i];
        }
        Print("#");
        printf(" ###%c#%c#%c#%c###\n", rooms[0][0], rooms[1][0], rooms[2][0], rooms[3][0]);
        for(int i = 1; i < rooms[0].size(); ++i){
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

    int targetRoom(char amphipod){
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
        for (int h = 0; h < hallway.size(); ++h){
            if (isClear(hallway[h])){
                continue;
            }
            char amphipod = hallway[h];
            // Room the amphipod wants
            int r = targetRoom(amphipod);
            // Room must be empty or only have the same amphipod
            if (!allCozy(r)){
                continue;
            }
            // Check the steps along the hallway
            int hr = outsideDoor(r);
            assert(h != hr);
            int dir = h < hr ? +1 : -1;
            int hc = h + dir;
            int steps = 1;
            while (hc != hr && isClear(hallway[hc])){
                hc += dir;
                ++steps;
            }
            if (!isClear(hallway[hc])){
                // Hallway blocked
                continue;
            }
            // Move in
            int i = 0;
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

bool operator<(Burrow const &b1, Burrow const &b2){
    if(b1.hallway < b2.hallway){
        return true;
    }
    if(b2.hallway < b1.hallway){
        return false;
    }

    return b1.rooms < b2.rooms;
}

pair<int, list<Burrow>> search(Burrow &start){
    multimap<int, list<Burrow>> to_search;
    to_search.emplace(0, list<Burrow>(1, start));

    // Pointer from final burrow state to corresponding entry in
    // to_search
    map<Burrow, decltype(to_search)::iterator> path_to;
    path_to[start] = to_search.begin();

    while(!to_search.empty()){
        auto cb = *to_search.begin();
        int cost = cb.first;
        list<Burrow> &bs = cb.second;
        Burrow &b = bs.back();

        // remove from path_to()
        auto pt = path_to.find(b);
        assert(pt != path_to.end() && pt->second == to_search.begin());
        path_to.erase(pt);
        to_search.erase( to_search.begin() );

        if(b.allHome()){
            return cb;
        }
        for(auto &next : b.successor()){
            int next_cost = cost + next.second;
            auto pt = path_to.find(next.first);
            if(pt != path_to.end()){
                if(pt->second->first <= next_cost){
                    // Already reached this state via a path that's at least as
                    // good
                    continue;
                }
                to_search.erase(pt->second);
                path_to.erase(pt);
            }
            auto next_bs(bs);
            next_bs.push_back(next.first);
            path_to[next.first] = to_search.emplace(next_cost, next_bs);
        }
    }

    assert(false && "No Solution found");
}


/////////////////////////////////////
// FOR LONG BURROW
/////////////////////////////////////
// TODO : TOO MUCH Code duplication reduce this (e.g. with inheritance, template etc) !!!

class LongBurrow{
    public:
    array<char, 11> hallway;
    array< array<char, 4>, 4 > rooms;
    map<char, int> move_cost = {
        {'A',1},
        {'B',10},
        {'C',100},
        {'D',1000},
    };

    LongBurrow(array<char, 11> h, array< array<char, 4>, 4 > r){
        hallway = h;
        rooms = r;
    }

    void printBurrow(){
        cout<<" #############"<<"\n";
        cout<<" #";
        for(int i = 0; i < hallway.size(); i++){
            cout<<hallway[i];
        }
        cout<<"#";
        printf(" ###%c#%c#%c#%c###\n", rooms[0][0], rooms[1][0], rooms[2][0], rooms[3][0]);
        for(int i = 1; i < rooms[0].size(); ++i){
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

    int targetRoom(char amphipod){
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

    list<pair<LongBurrow, int>> moveOut(){
        list<pair<LongBurrow, int>> result;
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
                        LongBurrow next(*this);
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

    list<pair<LongBurrow, int>> moveIn(){
        list<pair<LongBurrow, int>> result;
        for (int h = 0; h < hallway.size(); ++h){
            if (isClear(hallway[h])){
                continue;
            }
            char amphipod = hallway[h];
            // Room the amphipod wants
            int r = targetRoom(amphipod);
            // Room must be empty or only have the same amphipod
            if (!allCozy(r)){
                continue;
            }
            // Check the steps along the hallway
            int hr = outsideDoor(r);
            assert(h != hr);
            int dir = h < hr ? +1 : -1;
            int hc = h + dir;
            int steps = 1;
            while (hc != hr && isClear(hallway[hc])){
                hc += dir;
                ++steps;
            }
            if (!isClear(hallway[hc])){
                // Hallway blocked
                continue;
            }
            // Move in
            int i = 0;
            ++steps;
            // All the way down
            while (i + 1 < rooms[r].size() && isClear(rooms[r][i + 1])) {
                i++;
                steps++;
            }
            LongBurrow next(*this);
            next.hallway[h] = '.';
            next.rooms[r][i] = amphipod;
            result.emplace_back(next, steps*move_cost[amphipod]);
        }

        return result;
    }

    list<pair<LongBurrow, int>> successor(){
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

bool operator<(LongBurrow const &b1, LongBurrow const &b2){
    if(b1.hallway < b2.hallway){
        return true;
    }
    if(b2.hallway < b1.hallway){
        return false;
    }

    return b1.rooms < b2.rooms;
}

pair<int, list<LongBurrow>> searchLong(LongBurrow &start){
    multimap<int, list<LongBurrow>> to_search;
    to_search.emplace(0, list<LongBurrow>(1, start));

    // Pointer from final burrow state to corresponding entry in
    // to_search
    map<LongBurrow, decltype(to_search)::iterator> path_to;
    path_to[start] = to_search.begin();

    while(!to_search.empty()){
        auto cb = *to_search.begin();
        int cost = cb.first;
        list<LongBurrow> &bs = cb.second;
        LongBurrow &b = bs.back();

        // remove from path_to()
        auto pt = path_to.find(b);
        assert(pt != path_to.end() && pt->second == to_search.begin());
        path_to.erase(pt);
        to_search.erase( to_search.begin() );

        if(b.allHome()){
            return cb;
        }
        for(auto &next : b.successor()){
            int next_cost = cost + next.second;
            auto pt = path_to.find(next.first);
            if(pt != path_to.end()){
                if(pt->second->first <= next_cost){
                    // Already reached this state via a path that's at least as
                    // good
                    continue;
                }
                to_search.erase(pt->second);
                path_to.erase(pt);
            }
            auto next_bs(bs);
            next_bs.push_back(next.first);
            path_to[next.first] = to_search.emplace(next_cost, next_bs);
        }
    }

    assert(false && "No Solution found");
}


int main() {
    // readFile("input.txt");

    // Part 1
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
    // b.printBurrow();
    auto cost_and_steps = search(b);
    cout<<cost_and_steps.first<<endl;// 14346

    // Part 2
    /* Input :
    #############
    #...........#
    ###D#A#C#D###
      #D#C#B#A#
      #D#B#A#C#
      #C#A#B#B#
      #########
    */
    array<char, 11> hallway2 = { '.','.','.','.','.','.','.','.','.','.', '.' };
    array< array<char, 4>, 4 > rooms2 = {{
        {{'D', 'D', 'D', 'C'}},
        {{'A', 'C', 'B', 'A'}},
        {{'C', 'B', 'A', 'B'}},
        {{'D', 'A', 'C', 'B'}}
    }};
    LongBurrow lb(hallway2, rooms2);
    // lb.printBurrow();
    auto cost_and_steps2 = searchLong(lb);
    cout<<cost_and_steps2.first<<endl;// 48984

    return 0;
}
