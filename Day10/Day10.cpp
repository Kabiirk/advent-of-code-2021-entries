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

int32_t findCompletionScore(string line){
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
    int32_t completion_score = 0;
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

int32_t partTwo(vector<string> lines){
    vector<int32_t> total_completion_scores;
    for(auto line : lines){
        int32_t completion_score = findCompletionScore(line);
        if(completion_score == 0) continue;
        total_completion_scores.push_back(completion_score);
    }

    sort(total_completion_scores.begin(), total_completion_scores.end());

    cout<<total_completion_scores.size()<<endl;
    printVector(total_completion_scores);
    return total_completion_scores[total_completion_scores.size()/2];
}



int main() {
    vector<string> sub_system = readFile("input.txt");
    // map<char, int> points = { {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137} };
    // map<char, char> pairs = { {'(',')'}, {'[',']'}, {'{','}'}, {'<','>'} };
    // string open_bracket = "([{<";
    // string close_bracket = ")]}>";
    // unsigned long long int part1 = 0;
    // vector<unsigned long long int> part2;

    // for(string line : sub_system){
    //     deque<char> stack;
    //     for(char c : line){
    //         if(open_bracket.find(c) != string::npos){
    //             stack.push_front(pairs[c]);
    //         }
    //         else if(c != stack.front()){
    //             stack.pop_front();
    //             part1 += points[c];
    //             break;
    //         }
    //         // else{
    //         //     unsigned long long int score = 0;
    //         //     for(auto d : stack){
    //         //         score = ((score * 5) + close_bracket.find(d)) + 1;
    //         //     }
    //         //     part2.push_back(score);
    //         // }
    //     }
    // }

    // Part 1
    cout<<partOne(sub_system)<<endl;// 387363

    // Part 2// 4330777059
             // 337301424
    cout<<partTwo(sub_system)<<endl;

    return 0;
}