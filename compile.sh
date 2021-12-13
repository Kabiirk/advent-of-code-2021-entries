if [ $# -ne 1 ]
  then
    echo "Improper number of arguments supplied"
    exit 1
fi

# if [ -d  "$1" ]
#   then
#     echo "Folder by this name exists"
#     echo "Choose a different name"
#     exit 1
# fi

cd Day$1/

C:/MinGW/bin/gcc Day$1.c -o Day$1.exe

cd ..