#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
// #include "../utils/utils.h"

using namespace std;

using IMAGE = vector< string >;

IMAGE readFile(string filename){
    string line;
    ifstream myfile (filename);
    IMAGE image;

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            if(line.size() == 0){
                continue;
            }
            else{
                string s;
                for(char l : line){
                    s+= l=='#' ? '1' : '0';
                }
                image.push_back(s);
            }
        }
    }
    else cout << "Unable to open file";

    return image;
}

void resizeImage(IMAGE &image){
    int n = image[0].size();
    image.insert(image.begin(), string(n, '0'));//top
    image.push_back(string(n, '0'));// bottom

    // left
    for(auto &row : image){
        row.insert(row.begin(), '0');
    }
    // right
    for(auto &row : image){
        row.push_back('0');
    }
}

void enhanceImage(IMAGE &image, string &program){
    IMAGE output = image;
    for(int y = 0; y<image.size(); y++){
        string row = image[y];

        for(int x = 0; x<row.size(); x++){
            string neighbours;

            for(int j = y-1; j<=y+1; j++){
                for(int i = x-1; i<=x+1; i++){
                    // handle boundaries
                    if(j<0 || j>=image.size()){
                        neighbours.push_back('0');
                    }
                    else if(i<0 || i>=image[j].size()){
                        neighbours.push_back('0');
                    }
                    else{
                        neighbours.push_back(image[j][i]);
                    }
                }
            }
            output[y][x] = program[stoi(neighbours, nullptr, 2)];
        }
    }

    image = output;
}

int whitePixelCount(IMAGE &image){
    int count = 0;

    for(auto row : image){
        for(auto col : row){
            if(col=='1'){
                count++;
            }
        }
    }

    return count;
}

int main() {
    IMAGE image = readFile("input.txt");
    int part_1, part_2;
    
    // Popping first element of vector since
    // it is the image enhancement algorithm
    string program = image[0];
    image.erase(image.begin());

    // printVector(image, true);
    // resizeImage(image);
    // printVector(image, true);

    for(int i = 1; i<=50; i++){
        resizeImage(image);
        enhanceImage(image, program);
        // after 2 enhancements
        if(i == 2){
            part_1 = whitePixelCount(image);
        }
    }

    // after 50 enhancements
    part_2 = whitePixelCount(image);

    // Part 1
    cout<<part_1<<endl;// 5081

    // Part 2
    cout<<part_2<<endl;// 15088

    return 0;
}