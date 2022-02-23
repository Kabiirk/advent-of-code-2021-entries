#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <set>
#include <regex>

using namespace std;

using COORDS = tuple<int, int, int>;
using SCANNER = vector< COORDS >;
using SCANNER_REPORT = vector< SCANNER >;

SCANNER_REPORT readFile(string filename){
    /*
    Required return Structure
    scanners = 
    <
        <
            (-730, 602, -747),
            (-722, -633, 630),
            ..
        >,

        <
            (23, -80, -134),
            (-593, -338, -790),
            ..
        >,

        ....
    >
    */
    string line;
    ifstream myfile (filename);
    SCANNER_REPORT scanners;
    int i=0;

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            // cout<<line<<endl;
            const regex r1("--- scanner (-?\\d*) ---");
            const regex r2("(-?\\d*),(-?\\d*),(-?\\d*)");
            smatch result1;
            smatch result2;

            // result = [ "-730,602,-747", "-730", "602", "-747" ]
            if (regex_search(line, result1, r1)) {
                // cout<<line<<endl;
                SCANNER v;
                scanners.push_back(v);
                i++;
            }
            else if (regex_search(line, result2, r2)){
                    // cout<<i-1<<" "<<line<<endl;
                    scanners[i-1].push_back(make_tuple(stoi(result2[1]), stoi(result2[2]), stoi(result2[3])));
                }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    // remove an empty vector at the end
    // scanners.pop_back();

    return scanners;

}

// utility function specifically for this problem
void printTuple(COORDS tup){
    cout<<"("<<get<0>(tup)<<", "<<get<1>(tup)<<", "<<get<2>(tup)<<"); ";
}

void printOneScannerReport(SCANNER scanner_report){
    cout<<"< "<<endl;
    for(auto coord_tuple : scanner_report){
        printTuple(coord_tuple);
    }
    cout<<" >"<<endl;
}

void printAllScannerReports(SCANNER_REPORT scanner_reports){
    cout<<"< "<<endl;
    for(auto scanner_report : scanner_reports){
        printOneScannerReport(scanner_report);
    }
    cout<<" >"<<endl;
}

void printTupleSet(set<COORDS> s){
    cout<<"( "<<endl;
    for(auto tup : s){
        printTuple(tup);
    }
    cout<<" )"<<endl;
}

int main() {
    SCANNER_REPORT scanners = readFile("input.txt");
    // printAllScannerReports(scanners);
    // printOneScannerReport(scanners[0]);

    set<COORDS> grid(scanners[0].begin(), scanners[0].end());
    scanners.erase(scanners.begin());
    // printOneScannerReport(scanners[0]);
    // printTupleSet(grid);

    // Part 1// 332

    // Part 2// 8507

    return 0;
}