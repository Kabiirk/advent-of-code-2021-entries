#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stack>
#include "../utils/utils.h"

using namespace std;

vector<string> readFile(string filename){
    string line;
    ifstream myfile (filename);
    vector<string> sub_system;

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            sub_system.push_back(line);
        }
    }
    else cout << "Unable to open file";

    return sub_system;
}

int findErrorScore(string line){
    stack<char> parentheses;
    for(char c : line){
        switch(c){
            case '(':
            case '[':
            case '{':
            case '<':
                parentheses.push(c);
                break;
            case ')':
                if(parentheses.empty() || parentheses.top() != '('){
                    return 3;
                }
                parentheses.pop();
                break;
            case ']':
                if(parentheses.empty() || parentheses.top() != '['){
                    return 57;
                }
                parentheses.pop();
                break;
            case '}':
                if(parentheses.empty() || parentheses.top() != '{'){
                    return 1197;
                }
                parentheses.pop();
                break;
            case '>':
                if(parentheses.empty() || parentheses.top() != '<'){
                    return 25137;
                }
                parentheses.pop();
                break;
            default:
                return 0;
        }
    }
    // to handle if line has no errors i.e isn't corrupted;
    return 0;
}

int64_t findCompletionScore(string line){
    stack<char> parentheses;
    for(char c : line){
        switch(c){
            case '(':
            case '[':
            case '{':
            case '<':
                parentheses.push(c);
                break;
            case ')':
                if(parentheses.empty() || parentheses.top() != '('){
                    return 0;
                }
                parentheses.pop();
                break;
            case ']':
                if(parentheses.empty() || parentheses.top() != '['){
                    return 0;
                }
                parentheses.pop();
                break;
            case '}':
                if(parentheses.empty() || parentheses.top() != '{'){
                    return 0;
                }
                parentheses.pop();
                break;
            case '>':
                if(parentheses.empty() || parentheses.top() != '<'){
                    return 0;
                }
                parentheses.pop();
                break;
            default:
                return 0;
        }
    }
    // to handle if line has no errors i.e isn't corrupted;
    int64_t completion_score = 0;
    while(!parentheses.empty()){
        completion_score *= 5;
        switch (parentheses.top()){
            case '(':
                completion_score+=1;
                break;
            case '[':
                completion_score+=2;
                break;
            case '{':
                completion_score+=3;
                break;
            case '<':
                completion_score+=4;
                break;
        }
        parentheses.pop();
    }
    return completion_score;
}

int partOne(vector<string> lines){
    int total_error_score=0;
    for(auto line : lines){
        total_error_score += findErrorScore(line);
    }

    return total_error_score;
}

int64_t partTwo(vector<string> lines){
    vector<int64_t> total_completion_scores;
    for(auto line : lines){
        int64_t completion_score = findCompletionScore(line);
        if(completion_score == 0) continue;
        total_completion_scores.push_back(completion_score);
    }
    sort(total_completion_scores.begin(), total_completion_scores.end());

    return total_completion_scores[total_completion_scores.size()/2];
}



int main() {
    vector<string> sub_system = readFile("input.txt");

    // Part 1
    cout<<partOne(sub_system)<<endl;// 387363

    // Part 2
    cout<<partTwo(sub_system)<<endl;// 4330777059

    return 0;
}