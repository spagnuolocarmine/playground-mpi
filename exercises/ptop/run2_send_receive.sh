#!/bin/bash

echo -e "Compiling"
cd /project/target/ptop
rm -rf out hw
mpicc -o hw send_receive.c 2> err_log
rc=$?
if [[ $rc != 0 ]]; then
    echo -e "Error : mpicc returned"
    cat err_log
    echo "TECHIO> success false"
    rm -rf out
    exit $rc
fi
echo "Compilation is OK"
rm -rf out
mkdir out
rc=0

echo -e "Execution ... "
mpirun --allow-run-as-root  -mca btl sm,tcp,self -np 2 -output-filename out/out ./hw
cat out/*
rm -rf out
echo "TECHIO> success true"