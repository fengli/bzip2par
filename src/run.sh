#!/bin/bash

./obzip2 input.txt
mv out.compress.7 out.compress.7.1
./bbzip2 input.txt
echo "===>testing correctness by comparing zipped file"
difference=`diff out.compress.7*`
if ["$difference" -eq ""]
then
    echo "===>compared success!"
else
    echo "===>failed"
fi