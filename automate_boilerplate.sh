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

mkdir $1/

echo "fn main() {
    println!(\"Hello World!\");
}" > $1/$1part1.rs;

echo "fn main() {
    println!(\"Hello World!\");
}" > $1/$1part2.rs;

echo "
--- $1: ---

> **My Answer :** 
[Code]()
 
------
 
--- $1: (Part Two) ---

> **My Answer :** 
[Code]()
" > $1/README.md