if [ $# -ne 1 ]
  then
    echo "Improper number of arguments supplied"
    exit 1
fi

cd Day$1
./Day$1
cd ..