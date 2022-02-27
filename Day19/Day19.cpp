#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <set>
#include <map>
#include <regex>
#include <cmath>
#include "../utils/utils.h"

using namespace std;

using COORDS = tuple<int, int, int>;
using SCANNER = vector< COORDS >;
using SCANNER_REPORT = vector< SCANNER >;
using CONFIG = map< COORDS, set<int> >;

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

void printMapOfPairs(map<int, pair<int, int>> rot){
    for(auto r : rot){
        cout<<r.first<<": "<<"("<<r.second.first<<","<<r.second.second<<") ";
    }
    cout<<endl;
}

template <typename T>
void Print(T s){
    cout<<s<<endl;
}

int getIndex(vector<int> v, int K)
{
    auto it = find(v.begin(), v.end(), K);
 
    // If element was found
    if (it != v.end())
    {
     
        // calculating the index
        // of K
        int index = it - v.begin();
        return index;
    }
    else {
        // If the element is not
        // present in the vector
        return -1;
    }
}

int getTupleValue(COORDS tup, const int i){
    // Switch-case not working for some reason
    // switch (i)
    // {
    // case 0 : return get<0>(tup);
    // case 1 : return get<1>(tup);
    // case 2 : return get<2>(tup);
    // }
    if(i == 0){
        return get<0>(tup);
    }
    else if(i==1){
        return get<1>(tup);
    }
    else if(i==2){
        return get<2>(tup);
    }
    else if(i==-1){
        return get<2>(tup);
    }
    else if(i==-2){
        return get<1>(tup);
    }
}

int distance(COORDS p1, COORDS p2){
    int dx = get<0>(p1) - get<0>(p2);
    int dy = get<1>(p1) - get<1>(p2);
    int dz = get<2>(p1) - get<2>(p2);

    return int(sqrt( (dx*dx) + (dy*dy) + (dz*dz) ) );
}

int TaxiDistance(COORDS p1, COORDS p2){
    int dx = get<0>(p1) - get<0>(p2);
    int dy = get<1>(p1) - get<1>(p2);
    int dz = get<2>(p1) - get<2>(p2);

    return abs(dx) + abs(dy) + abs(dz);
}

int getCommonPtNum(CONFIG config_1, CONFIG config_2){
    int max_len = 0;

    // p0 & p1 are standalone std::pair<const COORDS, std::set<int>>
    // so we need to access the corresponding set via ".second"
    for(auto p0 : config_1){
        for(auto p1 : config_2){
            set<int> intersection;
            set_intersection(p0.second.begin(), p0.second.end(), p1.second.begin(), p1.second.end(),
                     inserter(intersection, intersection.begin()));
            if(intersection.size() > max_len){
                max_len = intersection.size();
            }
        }
    }

    return max_len;
}

CONFIG getConfig(set<COORDS> sensor_data){
    CONFIG config;
    for(auto p1 : sensor_data){
        for(auto p2 : sensor_data){
            config[p1].insert(distance(p1, p2));
        }
    }

    return config;
}

// rot  {0: (2, 1), 1: (0, 1), 2: (1, 1)}
// translation  [-1103, -2383, -1149]
pair<map<int, pair<int, int>>, vector<int>> allign(CONFIG &config1, CONFIG &config2){
    map<COORDS, COORDS> mapping;
    for(auto p1 : config1){
        for(auto p2 : config2){
            // Takes VEEEEERY Long 
            vector<int> intersection;
            set_intersection(p1.second.begin(), p1.second.end(), p2.second.begin(), p2.second.end(),
                     back_inserter(intersection));
            if(intersection.size() > 10){
                mapping[p1.first] = p2.first;
            }
        }
    }


    double sum_1_x=0.0, sum_1_y=0.0, sum_1_z=0.0;
    double sum_2_x=0.0, sum_2_y=0.0, sum_2_z=0.0;
    double len_mapping = mapping.size();

    for(auto k : mapping){
            sum_1_x += get<0>(k.first);
            sum_1_y += get<1>(k.first);
            sum_1_z += get<2>(k.first);

            sum_2_x += get<0>(k.second);
            sum_2_y += get<1>(k.second);
            sum_2_z += get<2>(k.second);
    }

    // This WORKS but all values are close to (not same as) the python solution
    double cog_1_x=sum_1_x/len_mapping;
    double cog_1_y=sum_1_y/len_mapping;
    double cog_1_z=sum_1_z/len_mapping;
    double cog_2_x=sum_2_x/len_mapping;
    double cog_2_y=sum_2_y/len_mapping;
    double cog_2_z=sum_2_z/len_mapping;

    COORDS p1 = mapping.begin()->first;
    COORDS p2 = mapping.at(p1);

    // p1_mod, p2_mod = (-857, 131, 516), (131, 516, -857)
    COORDS p1_mod = make_tuple(
        round( get<0>(p1)-cog_1_x ),
        round( get<1>(p1)-cog_1_y ),
        round( get<2>(p1)-cog_1_z )
    );
    COORDS p2_mod = make_tuple(
        round(get<0>(p2)-cog_2_x),
        round(get<1>(p2)-cog_2_y),
        round(get<2>(p2)-cog_2_z)
    );

    map<int, pair<int, int>> rot;
    // the value of 'i' is not usable in a constant expression
    // int temp = get<i>(tuple);
    // needed to make the getTupleVal() ugliness because of this :(
    // temp = list(map(abs, p2_mod)) => [131, 516, 857]
    vector<int> temp = { abs(get<0>(p2_mod)), abs(get<1>(p2_mod)), abs(get<2>(p2_mod)) };
    for(int i = 0; i<3; i++){
        int idx =  getIndex( temp, (int)abs( getTupleValue(p1_mod, i) ) );
        // ALL VALS WRONG !! but this somehow works
        // if(i==1){
        //     printVector(temp);
        //     Print(idx);
        //     Print( (int)abs( getTupleValue(p1_mod, i) ) );
        // }
        rot[i] = make_pair(idx, getTupleValue(p1_mod, i)/getTupleValue(p2_mod, idx));
    }

    vector<int> p2_rot = {0, 0, 0};
    for(int j = 0; j<3; j++){
        p2_rot[j] = getTupleValue(p2, rot[j].first) * rot[j].second;
    }

    vector<int> translation;
    for(int k = 0; k<3; k++){
        translation.push_back(p2_rot[k] - getTupleValue(p1, k) );
    }

    return make_pair(rot, translation);
}

set<COORDS> transformPoints(map<int, pair<int, int>> rot, vector<int> trans, SCANNER points){
    set<COORDS> new_points;
    // p is a tuple<int, int, int> i.e. COORDS
    for(auto p : points){
        COORDS t_t  = make_tuple( 
                ( getTupleValue(p, rot[0].first) * rot[0].second) - trans[0],
                ( getTupleValue(p, rot[1].first) * rot[1].second) - trans[1],
                ( getTupleValue(p, rot[2].first) * rot[2].second) - trans[2]
            );
        new_points.insert( t_t );
    }

    return new_points;
}

pair<SCANNER, int> part1(SCANNER_REPORT scanners){
    set<COORDS> grid(scanners[0].begin(), scanners[0].end());
    scanners.erase(scanners.begin());
    /*
    scanner_pos = [[-35, -41, -1043], [-3, -122, -2402], 
                   [-30, -58, -3463], [-21, -1221, -3496],...
                   .., [-1103, -1340, -1046], [-1103, -2383, -1149]]
    */
    vector<COORDS> scanner_pos;
    while(scanners.size() > 0){
        CONFIG grid_config = getConfig(grid);
        vector<int> scanners_common;
        for(auto s: scanners){
            set<COORDS> s_set(s.begin(), s.end());
            scanners_common.push_back( getCommonPtNum( grid_config, getConfig(s_set) ) );
        }

        int t = *max_element(scanners_common.begin(), scanners_common.end());
        int s = getIndex( scanners_common, t );

        // possible reason for difference, get_config() in python
        // solution can take 2nd argument of both type set and list,
        // but here getConfig() can only take type set as 2nd argument.
        set<COORDS> max_scan(scanners[s].begin(), scanners[s].end());

        // Since we are passing it by reference in allign function,
        // we need to do this to avoid the following error :
        // invalid initialization of non-const reference of type 'CONFIG& {aka std::map<std::tuple<int, int, int>, std::set<int> >&}' from an rvalue of type 'CONFIG {aka std::map<std::tuple<int, int, int>, std::set<int> >}'
        //  pair<map<int, pair<int, int>>, vector<int>> temp_pair = allign(grid_config, getConfig(max_scan));
        // Ref. : https://stackoverflow.com/questions/8293426/error-invalid-initialization-of-non-const-reference-of-type-int-from-an-rval
        CONFIG c = getConfig(max_scan);

        pair<map<int, pair<int, int>>, vector<int>> temp_pair = allign(grid_config, c);
        map<int, pair<int, int>> rot = temp_pair.first;
        vector<int> trams = temp_pair.second;

        set<COORDS> s1 = transformPoints(rot, trams, scanners[s]);
        // ~ grid.update()
        for(auto a : s1){
            grid.insert(a);
        }

        auto i = find(scanners.begin(), scanners.end(), scanners[s]);
        scanners.erase(i);

        scanner_pos.push_back( make_tuple( trams[0], trams[1], trams[2] ) );
    }

    return make_pair(scanner_pos, grid.size());
}

int part_2(SCANNER scanner_pos){
    vector<int> taxi_distance;
    for(auto c1 : scanner_pos){
        for(auto c2 : scanner_pos){
            taxi_distance.push_back( TaxiDistance(c1, c2) );
        }
    }

    return *max_element(taxi_distance.begin(), taxi_distance.end());
}

int main(){
    SCANNER_REPORT scanners = readFile("input.txt");

    pair<SCANNER, int> part_1 = part1(scanners);

    // Part 1
    cout<<part_1.second<<endl;// 332

    // Part 2
    cout<<part_2(part_1.first)<<endl;// 8507

    return 0;
}