#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>
#include <variant>
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

class Number{
    public:
        static unique_ptr<Number> parse(string rep, Number* parent = nullptr){
            auto num = make_unique<Number>();
            num->parent_ = parent;

            if(rep.front()=='['){}
            int depth = 0;
            int comma = -1;
            for(int pos = 0; pos<rep.size(); pos++){
                switch(rep[pos]){
                    case '[':
                        depth++;
                        break;
                    case ']':
                        depth--;
                        break;
                    case ',':
                        if(depth == 1){
                            comma = pos;
                        }
                        break;
                }
            }
            if(depth==0){};
            if(comma != -1){};

            string left_rep = rep.substr(1,comma-1);
            string right_rep = rep.substr(comma+1);
            right_rep.pop_back();

            int left_int = 0;
            if(stoi(left_rep)){
                num->left_ = left_int;
            }
            else{
                num->left_ = parse(left_rep, num.get());
            }

            int right_int = 0;
            if(stoi(right_rep)){
                num->right_ = right_int;
            }
            else{
                num->right_ = parse(right_rep, num.get());
            }

            return num;
        }

        static unique_ptr<Number> add(unique_ptr<Number> left, unique_ptr<Number> right){
            auto num = make_unique<Number>();
            left->parent_ = num.get();
            right->parent_ = num.get();
            num->left_ = move(left);
            num->right_ = move(right);

            return num;
        }


        void reduce(){
            for(;;){
                if(maybeExplode(1)){
                    continue;
                }
                if(maybeSplit()){
                    continue;
                }
                return;
            }
        }

        int64_t magnitude() const {
            int mag = 0;
            if(left_.index() == 0){
                mag+= 3*get<0>(left_);
            }
            else{
                mag += 3*get<1>(left_)->magnitude();
            }
            if(right_.index() == 0){
                mag+= 2*get<0>(right_);
            }
            else{
                mag += 2*get<1>(right_)->magnitude();
            }

            return mag;
        }

    private:
    int Explode() const {
            if(holds_alternative<int>(left_)){}
            if(holds_alternative<int>(right_)){}
            int* left_of_pair = findLeft();
            if(left_of_pair != nullptr){
                *left_of_pair += get<0>(left_);
            }

            int* right_of_pair = findRight();
            if(right_of_pair != nullptr){
                *right_of_pair += get<0>(right_);
            }

            return 0;
        }

        unique_ptr<Number> split(int value){
            auto num = make_unique<Number>();
            num->parent_ = this;
            num->left_ = static_cast<int>(floor(static_cast<double>(value)/2.0));
            num->right_ = static_cast<int>(ceil(static_cast<double>(value)/2.0));

            return num;
        }

        bool maybeExplode(int depth){
            if(depth == 4){
                if(left_.index() == 1){
                    left_ = get<1>(left_)->Explode();
                    return true;
                }
                
                if(right_.index() == 1){
                    right_ = get<1>(right_)->Explode();
                    return true;
                }
            }
            if(left_.index() == 1 && get<1>(left_)->maybeExplode(depth+1)){
                return true;
            }
            if(right_.index() == 1 && get<1>(right_)->maybeExplode(depth+1)){
                return true;
            }

            return false;
        }

        bool maybeSplit(){
            if(left_.index() == 0 && get<0>(left_)>=10){
                left_ = split(get<0>(left_));
                return true;
            }
            if(left_.index() == 1 && get<1>(left_)->maybeSplit()){
                return true;
            }

            if(right_.index() == 0 && get<0>(right_)>=10){
                right_ = split(get<0>(right_));
                return true;
            }
            if(right_.index() == 1 && get<1>(right_)->maybeSplit()){
                return true;
            }

            return false;
        }

        int* leftMost(){
            if(left_.index() == 0){
                return &get<0>(left_);
            }
            return get<1>(left_)->leftMost();
        }
        int* rightMost(){
            if(right_.index() == 0){
                return &get<0>(right_);
            }
            return get<1>(right_)->rightMost();
        }

        int* findLeft() const {
            if(parent_ == nullptr){
                return nullptr;
            }
            if(parent_->left_.index() == 1 && get<1>(parent_->left_).get() == this){
                return parent_->findLeft();
            }
            if(parent_->right_.index() == 1 && get<1>(parent_->right_).get() == this){
            }

            if(parent_->left_.index() == 0){
                return &get<0>(parent_->left_);
            }
            return get<1>(parent_->left_)->rightMost();
        }

        int* findRight() const {
            if(parent_ == nullptr){
                return nullptr;
            }
            if(parent_->right_.index() == 1 && get<1>(parent_->right_).get() == this){
                return parent_->findRight();
            }
            if(parent_->left_.index() == 1 && get<1>(parent_->left_).get() == this){
            }

            if(parent_->right_.index() == 0){
                return &get<0>(parent_->right_);
            }
            return get<1>(parent_->right_)->leftMost();
        }

        Number* parent_ = nullptr;
        variant<int, unique_ptr<Number>> left_;
        variant<int, unique_ptr<Number>> right_;
};

int main() {
    vector<string> blowfish_numbers = readFile("input.txt");

    unique_ptr<Number> result = Number::parse(blowfish_numbers.front());
    for(auto line = blowfish_numbers.begin()+1; line != blowfish_numbers.end(); ++line){
        unique_ptr<Number> next = Number::parse(*line);
        result = Number::add(move(result), move(next));
        result->reduce();
    }

    Print(result->magnitude());

    return 0;
}