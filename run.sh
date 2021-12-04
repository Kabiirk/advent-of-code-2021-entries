if [ $# -ne 1 ]
  then
    echo "Improper number of arguments supplied"
    exit 1
fi

cd $1
./$1
cd ..