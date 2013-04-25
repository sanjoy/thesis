#!/bin/bash

cd profiles
./backup-scores.sh
cd ..

declare -a FAST=(bubble-sort insertion-sort quick-sort merge-sort std-sort \
    stepanov-abstraction stepanov-vector)
declare -a SLOW=(loop-unroll mao-cfg-loop-structure-graph)

for bench_type in ${FAST[@]}; do
    ./generate-energy-profile.sh 15 $bench_type
    echo "Cooldown!"
    sleep 15
done

for bench_type in ${SLOW[@]}; do
    ./generate-energy-profile.sh 10 $bench_type
    echo "Cooldown!"
    sleep 15
done
