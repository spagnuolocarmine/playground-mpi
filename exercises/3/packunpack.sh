#!/bin/bash
NAME="packunpack"
echo -e "Compiling"
cd /project/target/3
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
mpirun --allow-run-as-root  -mca btl sm,tcp,self -np 2 -output-filename out/out ./$NAME
cat out/*
rm -rf out
echo -e "Done."
echo "TECHIO> success true"