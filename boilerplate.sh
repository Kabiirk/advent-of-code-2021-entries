if [ $# -ne 1 ]
  then
    echo "Improper number of arguments supplied"
    exit 1
fi

if [ -d  "$1" ]
  then
    echo "Folder by this name exists"
    echo "Choose a different name"
    exit 1
fi

mkdir Day$1/

echo "
print(\"Hello World\")
" > Day$1/Day$1.py;

echo "#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readFile(string filename){
    string line;
    ifstream myfile (filename);

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            cout<<line<<endl;
        }
    }
    else cout << \"Unable to open file\";
}

int main() {
    cout<<\"Hello World!\"<<endl;

    return 0;
}" > Day$1/Day$1.cpp;

echo "
### **--- $1: ---**

> **My Answer :**

[Code]()
 
------
 
### **--- $1: (Part Two) ---**

> **My Answer :**

[Code]()
" > Day$1/README.md