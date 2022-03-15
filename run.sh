# How to Run :
# for Python Solution
# bash run.sh XX py 

# for C++ Solution
# bash run.sh XX cpp

# where XX => 01, 02, 03 ... 23, 24, 25

# E.g. :
# 1.
# bash run.sh 01 cpp
# executes the C++ solution for Day01

# 2. 
# bash run.sh 22 py
# executes the python solution for Day22

if [ $# -ne 2 ]
  then
    echo "Improper number of arguments supplied"
    echo "Arguments should be of form :"
    echo "'bash run.sh XX cpp'"
    echo "or"
    echo "'bash run.sh XX py'"
    exit 1
fi

if [ $1 = "test_utils" ];then
    ./utils/$1
    exit 1
fi

cd Day$1
if [ $2 = "cpp" ];then
    ./Day$1
else
    python Day$1.py
fi
cd ..