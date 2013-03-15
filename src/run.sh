#!/bin/bash

./obzip2 gdb.tar
mv out.compress.7 out.compress.7.1
./bbzip2 gdb.tar
echo "===>testing correctness by comparing zipped file"
difference=`diff out.compress.7*`
if ["$difference" -eq ""]
then
    echo "===>compared success!"
else
    echo "===>failed"
fi