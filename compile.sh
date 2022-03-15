# compile.sh only required for C++ solutions
# For Python Solutions just simply type 
# bash run.sh XX py

# How to Run :
# bash compile.sh XX

# where XX => 01, 02, 03 ... 23, 24, 25

# E.g. :
# 1.
# bash compile.sh 01
# Compiles the C++ code for Day01

if [ $# -ne 1 ]
  then
    echo "Improper number of arguments supplied"
    echo "Arguments should be of form :"
    echo "'bash compile.sh XX'"
    exit 1
fi

if [ $1 = "test_utils" ]; then
    C:/MinGW/bin/g++ utils/$1.cpp -o utils/$1.exe
    exit 1
fi

cd Day$1/

C:/MinGW/bin/g++ Day$1.cpp -o Day$1.exe

cd ..