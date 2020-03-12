#!/bin/bash
NAME="gather"
echo -e "Compiling"
cd /project/target/4
rm -rf out $NAME
mpicc -o $NAME $NAME.c 2> err_log
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
mpirun --allow-run-as-root  -mca btl sm,tcp,self -np 8 -output-filename out/out ./$NAME
cat out/*
rm -rf out
echo -e "Done."
