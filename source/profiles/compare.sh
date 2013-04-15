#!/bin/sh

if [ -z $1 ]; then
    echo "Invalid arguments"
    echo "Usage $0 profile-base-name"
    exit 1
fi

BASE=$1

NORMAL_COST=`statistics < $BASE-normalopt-total | sed 's/("\(.*\)",.*/\1/'`
ENERGYOPT_COST=`statistics < $BASE-energyopt-total | sed 's/("\(.*\)",.*/\1/'`
IMPROVEMENT=`echo "scale=2; 100 * ($NORMAL_COST - $ENERGYOPT_COST) / $NORMAL_COST" | bc`

echo "Profiling $1 ..."
echo "Normal: $NORMAL_COST, EnergyOpt: $ENERGYOPT_COST, Improvement: $IMPROVEMENT%"
