#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <stack>
#include <algorithm>
#include "../utils/utils.h"

using namespace std;

using GRAPH = map<string, vector<string>>;
using MAP = map<string, int>;

struct RequiredData {
    GRAPH graph;
    MAP n_visits;
};

RequiredData readFile(string filename){
    /*
    Desired data structures :
    graph = {
                'LP': ['cb', 'yk', 'bf'],
                'cb': ['LP', 'end', 'lj', 'PK'],
                'PK': ['yk', 'my', 'cb', 'bf', 'start'],
                'yk': ['PK', 'BN', 'cd', 'bf', 'LP', 'EP'],
                'bf': ['end', 'yk', 'lj', 'BN', 'PK', 'LP'],
                'end': ['bf', 'cb', 'BN'],
                'my': ['PK', 'start', 'BN', 'lj'],
                'BN': ['yk', 'bf', 'end', 'my', 'lj'],
                'cd': ['yk'],
                'lj': ['cb', 'bf', 'BN', 'start', 'my'],
                'start': ['my', 'PK', 'lj'],
                'EP': ['yk']
            }
    n_visits = {
                'LP': 0,
                'cb': 0,
                'PK': 0,
                'yk': 0,
                'bf': 0,
                'end': 0,
                'my': 0,
                'BN': 0,
                'cd': 0,
                'lj': 0,
                'start': 0,
                'EP': 0
                }
    */
    string line;
    ifstream myfile (filename);
    RequiredData req_data;

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            // cout<<line<<endl;
            const regex r("(\\w+)-(\\w+)");
            smatch result;

            if (regex_search(line, result, r)) {
                // to make sure all nodes are covered
                req_data.graph[result[1]].push_back(result[2]);
                req_data.graph[result[2]].push_back(result[1]);
                req_data.n_visits[result[1]] = 0;
                req_data.n_visits[result[2]] = 0;
            }
        }
    }
    else cout << "Unable to open file";

    return req_data;
}

// Helper Function
void printGraph(GRAPH graph){
    for(GRAPH::const_iterator it = graph.begin(); it!=graph.end(); ++it){
        cout<<it->first<<" : ";
        printVector(it->second);
    }
    cout<<endl;
}

// recursive approach
int graphSearchRecursive(GRAPH &graph, MAP &n_visits, vector<string> &node_stack, string node, int &n_paths, bool doubles_allowed){
    if(n_visits.at(node) && islower(node[0])){
        if(!doubles_allowed || node=="start"){
            return n_paths;
        }
        doubles_allowed=false;
    }
    if(node=="end"){
        return n_paths+1;
    }
    else{
        node_stack.push_back(node);
        n_visits.at(node)+=1;
        int n = graph.at(node).size();
        for(int i = 0; i<n; i++){
            n_paths = graphSearchRecursive(graph, n_visits, node_stack, graph.at(node)[i], n_paths, doubles_allowed);
        }
        node_stack.pop_back();
        n_visits.at(node) -= 1;
        if(n_visits.at(node) && islower(node[0])){
            doubles_allowed = true;
        }
    }
    return n_paths;
}

// iterative approach
int graphSearchIterative(GRAPH graph, bool visit_twice=false){
    // setup for initial search state
    vector<vector<string>> finished_paths;
    vector<vector<string>> previous_paths;
    previous_paths.push_back(vector<string> {"start"});

    bool search_complete = false;
    while(!search_complete){
        search_complete = true;
        vector<vector<string>> current_paths;
        for(const auto& previous_path : previous_paths){
            const auto current_location = previous_path[previous_path.size()-1];
            const auto connected_caves = graph.at(current_location);
            for(const auto& cave : connected_caves){
                // start
                if(cave == "start"){
                    continue;
                }

                // end
                if(cave == "end"){
                    auto finished_path = previous_path;
                    finished_path.push_back(cave);
                    finished_paths.push_back(finished_path);
                    continue;
                }

                // small cave
                if(cave[0]>='a' && cave[0]<='z'){
                    auto already_visited = find(previous_path.begin(), previous_path.end(), cave) != previous_path.end();
                    if(already_visited){
                        if(!visit_twice){
                            continue;
                        }
                        auto already_visited_small_cave = false;
                        for(int i = 1; i<previous_path.size(); ++i){
                            const auto& previous_cave = previous_path[i];
                            if(previous_cave[0]>='a' && previous_cave[0]<='z'){
                                already_visited_small_cave = find(previous_path.begin()+i+1, previous_path.end(), previous_cave) != previous_path.end();
                                if(already_visited_small_cave){
                                    break;
                                }
                            }
                        }
                        if(already_visited_small_cave){
                            continue;
                        }
                    }
                }

                // big cave or unvisited small cave
                auto current_path = previous_path;
                current_path.push_back(cave);
                current_paths.push_back(current_path);
                search_complete = false;
            }
        }
        previous_paths = current_paths;
    }

    return finished_paths.size();
}


// Implemented both Recursive & Iterative approachess
int main() {
    RequiredData req_data = readFile("input.txt");
    GRAPH graph = req_data.graph;
    MAP n_visits = req_data.n_visits;
    vector<string> Stack;
    int n_paths = 0;

    // Part 1
    int part1 = graphSearchRecursive(graph, n_visits, Stack, "start", n_paths, false);
    // int part1_iterative = graphSearchIterative(graph);
    cout<<part1<<endl;// 3298
    
    // Reset some variables
    n_paths = 0;
    vector<string> Stack2;
    for(auto it = n_visits.begin(); it!=n_visits.end(); ++it ){
        it->second=0;
    }

    // Part 2
    int part2 = graphSearchRecursive(graph, n_visits, Stack2, "start", n_paths, true);
    // int part2_iterative = graphSearchIterative(graph, true);
    cout<<part2<<endl;// 93572

    return 0;
}