if [ $# -ne 1 ]
  then
    echo "Improper number of arguments supplied"
    exit 1
fi

if [ $1 = "test_utils" ];then
    ./utils/$1
    exit 1
fi

cd Day$1
./Day$1
cd ..