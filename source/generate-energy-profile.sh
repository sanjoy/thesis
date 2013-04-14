#!/bin/sh

if [ -z "$HARNESS" ]; then
    echo "HARNESS is not defined!  Please define it so that \$HARNESS {executable}"
    echo "runs wattage and emits the output to output.out"
    exit 1
fi

if [ $# -le 1 ]; then
    echo "Invalid usage!"
    echo "Usage: $0 iteration-count benchmark-executable {arguments}"
    exit 1
fi

ITERATIONS=$1
BASE=$2

shift
shift

mkdir -p profiles

for i in $(seq 1 $ITERATIONS); do
    echo "Running $BASE-normalopt $i"
    $HARNESS ./$BASE-normalopt $*
    cat output.out | tail -n 1 | awk '{ print $3 }' >> profiles/$BASE-normalopt-total

    echo "Running $BASE-energyopt $i"
    $HARNESS ./$BASE-energyopt $*
    cat output.out | tail -n 1 | awk '{ print $3 }' >> profiles/$BASE-energyopt-total
done

rm output.out
