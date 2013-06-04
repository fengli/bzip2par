#!/bin/bash

./icc_bzip2 gdb.tar
mv out.compress.7 out.compress.7.1
./icc_pbzip2 gdb.tar
echo "===>testing correctness by comparing zipped file"
difference=`diff out.compress.7*`
if ["$difference" -eq ""]
then
    echo "===>compared success!"
else
    echo "===>failed"
fi