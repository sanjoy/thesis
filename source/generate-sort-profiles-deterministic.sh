#!/bin/bash

cd profiles
./backup-scores.sh
cd ..

declare -a SORTS=(bubble-sort insertion-sort quick-sort merge-sort std-sort)

for bench_type in ${SORTS[@]}; do
    ./generate-energy-profile.sh 1 $bench_type
    echo "Cooldown!"
    sleep 2
done
