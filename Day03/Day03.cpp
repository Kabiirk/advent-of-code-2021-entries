#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> readFile(string filename){
    vector<string> report;
    string line;
    ifstream myfile (filename);

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            // cout<<line<<endl;
            report.push_back(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return report;
}

char CommonBit(vector<string> report, int position_to_check, string mode){
    int one = 0;
    int zero = 0;
    for(auto it : report){
        if(it[position_to_check] == '1'){
            one++;
        }
        else{
            zero++;
        }
    }

    if(mode == "most"){
        return (one >= zero) ? '1' : '0';
    }
    else{
        return (one < zero) ? '1' : '0';
    }
}

string toggleBinaryString(string binary_string){
    string result = "";
    for(char it : binary_string){
        if(it == '1'){
            result+='0';
        }
        else{
            result += '1';
        }
    }

    return result;
}

string recursiveSearch(vector<string> report, int position_to_check, string mode){
    char bit_to_compare;
    if(report.size() == 1){
        return report[0];
    }
    else{
        if(mode == "most"){
            bit_to_compare = CommonBit(report, position_to_check, "most");
        }
        else{
            bit_to_compare = CommonBit(report, position_to_check, "least");
        }
        vector<string> new_report;
        for(auto entry : report){
            if(entry[position_to_check] == bit_to_compare){
                new_report.push_back(entry);
            }
        }
        position_to_check++;
        return recursiveSearch(new_report, position_to_check, mode);
    }
}

int main() {
    vector<string> diagnostic_report = readFile("input.txt");

    // Part 1
    string gamma_rate_binary_string = "";
    int n = diagnostic_report[0].length();
    for(int i = 0; i<n; i++){
        gamma_rate_binary_string += CommonBit(diagnostic_report, i, "most");
    }
    string epsilon_rate_binary_string = toggleBinaryString(gamma_rate_binary_string);
    int gamma_rate = stoi(gamma_rate_binary_string, nullptr, 2);// 218
    int epsilon_rate = stoi(epsilon_rate_binary_string, nullptr, 2);// 3877

    cout<<gamma_rate * epsilon_rate<<endl;// 845186

    // Part 2
    string o2_gen_rating_binary_string = recursiveSearch(diagnostic_report, 0, "most");// 010110110011
    string co2_scrub_rating_binary_string = recursiveSearch(diagnostic_report, 0, "least");// 110001101010 

    int o2_gen_rate = stoi(o2_gen_rating_binary_string, nullptr, 2);// 1459
    int co2_scrub_rate = stoi(co2_scrub_rating_binary_string, nullptr, 2);// 3178

    cout<<o2_gen_rate * co2_scrub_rate<<endl;// 4636702
    return 0;
}