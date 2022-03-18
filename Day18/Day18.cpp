#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "../utils/utils.h"

using namespace std;

vector<string> readFile(string filename){
    vector<string> file_output;
    string line;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            file_output.push_back(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return file_output;
}

struct Node{
    int value = -1;
    int left_v = -1;
    int right_v = -1;
    Node* left = nullptr;
    Node* right = nullptr;
};

Node* convertToTree(string& s, int& index){
    auto n = new Node();
    if(s[index] == '['){
        if(s[index+1] == '['){
            index++;
            n->left = convertToTree(s, index);
        }
        else{
            const auto index2 = s.find(",", index+1);
            n->left_v = stoi(s.substr(index+1, index2-index-1));
            index = index2;
        }
    }

    if(s[index] == ','){
        if(s[index+1]=='['){
            index++;
            n->right = convertToTree(s, index);
        }
        else{
            const auto index2 = s.find("]", index+1);
            n->right_v = stoi(s.substr(index+1, index2-index-1));
            index = index2;
        }
    }

    index++;
    return n;
}

void setValueToNOne(Node* n){
    if(n->left_v == -1){
        setValueToNOne(n->left);
    }
    n->value = -1;
    if(n->right_v == -1){
        setValueToNOne(n->right);
    }
}

Node* checkExplode(Node* n, int level){
    if(level >= 4){
        if(n->left==nullptr && n->right==nullptr){
            return n;
        }
    }

    if(n->left != nullptr){
        auto returned_node = checkExplode(n->left, level+1);
        if(returned_node != nullptr){
          return returned_node;
        }
    }

    if(n->right != nullptr){
        auto returned_node = checkExplode(n->right, level+1);
        if(returned_node != nullptr){
          return returned_node;
        }
    }

    return nullptr;
}

pair<bool, Node*> traverseUpdateExplodedLR(Node* n, Node* exploded, Node*& prev){
    if(n->left_v != -1){
        prev=n;
    }
    else{
        if(n->left == exploded){
            if(prev != nullptr && prev->right == nullptr){
                prev->right_v += exploded->left_v;
            }
            else if(prev != nullptr && prev->left == nullptr){
                prev->left_v += exploded->left_v;
            }

            return make_pair(true, n);
        }
        else{
            // found_node = <bool, Node*>
            auto found_node = traverseUpdateExplodedLR(n->left, exploded, prev);
            if(found_node.first){
                return make_pair(true, found_node.second);
            }
        }
    }

    if(n->right_v != -1){
        prev=n;
    }
    else{
        if(n->right == exploded){
            if(prev != nullptr && prev->right == nullptr){
                prev->right_v += exploded->right_v;
            }
            else if(prev != nullptr && prev->left == nullptr){
                prev->left_v += exploded->left_v;
            }

            return make_pair(true, n);
        }
        else{
            // found_node = <bool, Node*>
            auto found_node = traverseUpdateExplodedLR(n->right, exploded, prev);
            if(found_node.first){
                return make_pair(true, found_node.second);
            }
        }
    }

    return make_pair(false, nullptr);
}

pair<bool, Node*> traverseUpdateExplodedRL(Node* n, Node* exploded, Node*& prev){
    if(n->right_v != -1){
        prev=n;
    }
    else{
        if(n->right == exploded){
            if(prev != nullptr && prev->left == nullptr){
                prev->left_v += exploded->right_v;
            }
            else if(prev != nullptr && prev->right == nullptr){
                prev->right_v += exploded->right_v;
            }

            return {true, n};
        }
        else{
            // found_node = <bool, Node*>
            auto found_node = traverseUpdateExplodedRL(n->right, exploded, prev);
            if(found_node.first){
                return {true, found_node.second};
            }
        }
    }

    if(n->left_v != -1){
        prev=n;
    }
    else{
        if(n->left == exploded){
            if(prev != nullptr && prev->left == nullptr){
                prev->left_v += exploded->right_v;
            }
            else if(prev != nullptr && prev->right == nullptr){
                prev->right_v += exploded->right_v;
            }

            return {true, n};
        }
        else{
            // found_node = <bool, Node*>
            auto found_node = traverseUpdateExplodedRL(n->left, exploded, prev);
            if(found_node.first){
                return {true, found_node.second};
            }
        }
    }

    return {false, nullptr};
}

bool explode(Node* root){
    auto prev = root;
    auto index = 0;
    auto exploded_node = checkExplode(root, index);
    if(exploded_node != nullptr){
          prev = nullptr;
          // found_to_update_l = <bool, Node*>
          auto found_to_update_l = traverseUpdateExplodedLR(root, exploded_node, prev);
          prev = nullptr;
          // found_to_update_r = <bool, Node*>
          auto found_to_update_r = traverseUpdateExplodedRL(root, exploded_node, prev);

          if(found_to_update_l.second!=nullptr && found_to_update_l.second->left == exploded_node){
              found_to_update_l.second->left = nullptr;
              found_to_update_l.second->left_v = 0;
          }
          if(found_to_update_r.second!=nullptr && found_to_update_r.second->right == exploded_node){
              found_to_update_r.second->right = nullptr;
              found_to_update_r.second->right_v = 0;
          }
          delete exploded_node;
    }

    return exploded_node!=nullptr;
}

bool split(Node* n){
    if(n->left == nullptr){
        if(n->left_v >= 10){
            n->left = new Node();
            n->left->left_v = n->left_v/2;
            n->left->right_v = n->left_v - n->left->left_v;
            n->left_v = -1;
            return true;
        }
    }
    else{
        auto found = split(n->left);
        if(found){
          return true;
        }
    }

    if(n->right == nullptr){
        if(n->right_v >= 10){
            n->right = new Node();
            n->right->left_v = n->right_v/2;
            n->right->right_v = n->right_v - n->right->left_v;
            n->right_v = -1;
            return true;
        }
    }
    else{
        auto found = split(n->right);
        if(found){
          return true;
        }
    }

    return false;
}

int findAppropriateAction(Node* n, int level){
    if(level >= 4 && n->left==nullptr && n->right==nullptr){
        return 1;// explodeable
    }

    if(n->left_v != -1){
        if(n->left_v >= 10){
            return 2;// splittable
        }
    }
    else{
        auto ans = findAppropriateAction(n->left, level+1);
        if(ans != 0){
            return ans;
        }
    }

    if(n->right_v != -1){
        if(n->right_v >= 10){
            return 2;// splittable
        }
    }
    else{
        auto ans = findAppropriateAction(n->right, level+1);
        if(ans != 0){
            return ans;
        }
    }

    return 0;
}

void sumNodes(Node *n){
    n->value = 0;

    if(n->left != nullptr){
        if(n->left->value == -1){
            sumNodes(n->left);
        }
        n->value += 3*n->left->value;
    }
    else{
        n->value += 3*n->left_v;
    }

    if(n->right != nullptr){
        if(n->right->value == -1){
            sumNodes(n->right);
        }
        n->value += 2*n->right->value;
    }
    else{
        n->value += 2*n->right_v;
    }
}

int partOne(vector<string> numbers){
    int len = numbers.size();

    string line = numbers[0];
    auto index = 0;
    auto prev = convertToTree(line, index);
    auto root = prev;

    for(int i = 1; i<len; i++){
        Node* n = new Node();
        n->left = prev;
        index = 0;
        n->right = convertToTree(numbers[i], index);
        prev = n;

        while(true){
            if(explode(n)){
                continue;
            }
            if(split(n)){
              continue;
            }

            break;
        }

        root = n;
    }

    setValueToNOne(root);
    sumNodes(root);

    return root->value;
}

int partTwo(vector<string> numbers){
    int max_val = numeric_limits<int>::min();
    int i1 = 0;
    int i2 = 0;

    int len = numbers.size();
    for(int i = 0; i<len; i++){
        for(int j = 0; j<len; j++){
            if(i==j){
                continue;
            }
            auto n = new Node();
            int index = 0;
            n->left = convertToTree(numbers[i], index);
            index = 0;
            n->right = convertToTree(numbers[j], index);

            while(true){
                if(explode(n)){
                    continue;
                }
                if(split(n)){
                    continue;
                }
                break;
            }

            setValueToNOne(n);
            sumNodes(n);

            if(n->value > max_val){
                i1 = i;
                i2 = j;
                max_val = n->value;
            }
        }
    }

    return max_val;
}

int main(){
    vector<string> blowfish_numbers = readFile("input.txt");
    // printVector(blowfish_numbers, true);

    // Part 1
    cout<<partOne(blowfish_numbers)<<endl;// 4057

    // Part 2
    cout<<partTwo(blowfish_numbers)<<endl;// 4683

    return 0;
}
