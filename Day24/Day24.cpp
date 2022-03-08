#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <regex>
// uncomment this if the custom swap() function isn't working
// #include <algorithm> // for swap()
#include "../utils/utils.h"

using namespace std;

using Instructions = vector< vector< string > >;

struct Result{
    string part1, part2;
};

Instructions readFile(string filename){
    string line;
    ifstream myfile (filename);
    Instructions data;
    vector<string> ins;

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            // cout<<line<<endl;
            bool is_input = line.find("inp")!=line.npos;
            if(is_input){
                data.push_back(ins);
                ins.clear();
            }
            else{
                ins.push_back(line);
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    // pushing basck last ins vector 
    data.push_back(ins);
    // removing the first empty ins vector added
    // during iteration;
    data.erase(data.begin());

    return data;
}

/*
data :
[
    [ 'mul x 0', 'add x z', 'mod x 26', ... ],
    [ 'mul x 0', 'add x z', 'mod x 26'  ... ],
    [ 'mul x 0', 'add x z', 'mod x 26'  ... ]
    ...
]

non_match :
[3, 4, 14]

diffs :
[
    [1, 10, 12],
    [1, 10, 10],
    [1, 12, 8],
    [1, 11, 4],
    ...
    [26, -12, 9]
]
q :
[(0, 12), (1, 10), (2, 8), (5, 10), (6, 6)]

mx :
[9, 3, 9, 5, 9, 9, 9, 3, 4, 2, 9, 8, 9, 9]

mn :
[1, 1, 8, 1, 5, 6, 7, 1, 1, 1, 7, 1, 2, 1]
*/

// helper function specifically for this problem
// using this just to avoid #include <algorithm>
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

Result solve(Instructions data){
    Result res;
    set<int> non_matching;
    vector<vector <int> > diffs;
    vector<pair<int, int>> q;
    vector<int> mx(14, 0);
    vector<int> mn(14, 0);
    const regex r("(\\w+) (w|x|y|z) (w|x|y|z|(-?\\d*))");

    vector< pair<int, string> > temp = vecEnumerate(data[0]);
    int n = data.size();
    for(auto e_x : temp){
        int e = e_x.first;
        string x = e_x.second;
        for(int y=0; y<n; y++){
            if(data[y][e] != x){
                non_matching.insert(e);
            }
        }
    }
    // printSet(non_matching);
    for(int i=0; i<n; i++){
        vector<int> temp;
        for(auto e : non_matching){  
            smatch result;
            // result = ["mul x 0", "mul", "x", "0"]
            if(regex_search(data[i][e], result, r)){
                temp.push_back(stoi(result[result.size()-1]));
            }
        }
        diffs.push_back(temp);
    }
    // print2DVec(diffs);

    auto temp2 = vecEnumerate(data);
    for(auto a_x : temp2){
        int a = a_x.first;
        vector<string> x = a_x.second;
        if(diffs[a][0]==1){
            q.push_back( make_pair( a, diffs[a][2] ) );
        }
        else{
            // ~ q.pop()
            // printVecPair(q);
            int b = q.back().first;
            int y = q.back().second;
            q.pop_back();
            int delta = y + diffs[a][1];
            if(!(delta >= 0)){
                // made my own custom function
                // if it isn't working,
                // just uncomment line 8 i.e. "#include <algorithm>"
                swap(a,b);
                delta = -delta;
            }
            mx[a] = 9;
            mx[b] = 9-delta;
            mn[a] = 1+delta;
            mn[b] = 1;
        }
    }
    // printVector(mx);
    // printVector(mn);

    res.part1 = joinVecAsString(mx);
    res.part2 = joinVecAsString(mn);

    return res;
}

int main() {
    Instructions data = readFile("input.txt");
    // print2DVec(data);

    Result res = solve(data);

    // Part 1
    cout<<res.part1<<endl;// 93959993429899

    // Part 2
    cout<<res.part2<<endl;// 11815671117121

    return 0;
}
