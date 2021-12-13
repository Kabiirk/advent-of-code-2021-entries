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

echo "#include<stdio.h>

int main() {
    printf(\"Hello World!\");
}" > Day$1/Day$1.c;

echo "
### **--- $1: ---**

> **My Answer :** 
[Code]()
 
------
 
### **--- $1: (Part Two) ---**

> **My Answer :** 
[Code]()
" > Day$1/README.md