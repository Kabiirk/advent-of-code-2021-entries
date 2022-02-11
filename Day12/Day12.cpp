#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <stack>
#include "../utils/utils.h"

using namespace std;

struct RequiredData {
    map<string, vector<string>> graph;
    map<string, int> n_visits;
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
                req_data.graph[result[1]].push_back(result[2]);
                req_data.graph[result[2]].push_back(result[1]);
                // to make sure all nodes are covered
                req_data.n_visits[result[1]] = 0;
                req_data.n_visits[result[2]] = 0;
            }
        }
    }
    else cout << "Unable to open file";

    return req_data;
}

void printGraph(map<string, vector<string>> graph){
    for(map<string, vector<string>>::const_iterator it = graph.begin(); it!=graph.end(); ++it){
        cout<<it->first<<" : ";
        printVector(it->second);
    }
    cout<<endl;
}

int graphSearch(map<string, vector<string>> graph, map<string, int> n_visits,stack<string> Stack, string node, int n_paths, bool doubles_allowed=false){
    if( n_visits[node] && isLowerString(node) ){
        if(!doubles_allowed || node=="start"){
            return n_paths;
        }
        doubles_allowed = false;
    }
    if(node == "end"){
        return n_paths+1;
    }
    else{
        Stack.push(node);
        n_visits[node]++;
        for(auto nb : graph[node]){
            n_paths = graphSearch(graph, n_visits, Stack, nb, n_paths, doubles_allowed);
        }
        Stack.pop();
        n_visits[node]--;
        if( n_visits[node] && isLowerString(node) ){
            doubles_allowed = true;
        }
    }

    return n_paths;
}

int main() {
    RequiredData req_data = readFile("input.txt");
    map<string, vector<string>> graph = req_data.graph;
    map<string, int> n_visits = req_data.n_visits;
    stack<string> Stack;
    int part1=0;
    int part2=0;
    // printGraph(graph);
    // printMap(n_visits);

    // Part 1
    part1 = graphSearch(graph, n_visits, Stack, "start", 0);
    cout<<part1<<endl;// 3928

    // Part 2
    part2 = graphSearch(graph, n_visits, Stack, "start", 0, true);
    cout<<part2<<endl;// 93572

    return 0;
}