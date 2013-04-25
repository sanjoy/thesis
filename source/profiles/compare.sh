#!/bin/sh

if [ -z $1 ]; then
    echo "Invalid arguments"
    echo "Usage $0 profile-base-name"
    exit 1
fi

BASE=$1

NORMAL_COST=`statistics < $BASE-normalopt-total | awk '{ print $1 }'`
NORMAL_SD=`statistics < $BASE-normalopt-total | awk '{ print $2 }'`
ENERGYOPT_COST=`statistics < $BASE-energyopt-total | awk '{ print $1 }'`
ENERGYOPT_SD=`statistics < $BASE-energyopt-total | awk '{ print $2 }'`
ABS_IMPROVEMENT=`echo "scale=2; $NORMAL_COST - $ENERGYOPT_COST" | bc`
IMPROVEMENT=`echo "scale=2; 100 * ($NORMAL_COST - $ENERGYOPT_COST) / $NORMAL_COST" | bc`

echo "Profiling $1 ..."
echo "Normal: $NORMAL_COST ($NORMAL_SD), EnergyOpt: $ENERGYOPT_COST ($ENERGYOPT_SD), Improvement: $IMPROVEMENT% ($ABS_IMPROVEMENT)"
