#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null

echo "--- Python Info"
which python3
python3 --version


echo "--- Analyze Files"
python3 avgBlockTime.py
feedback=$?


if [ 0 -eq ${feedback} ] ; then
    gnuplot -p avgBlockTime.gnuplot
fi

# Back to the original location
popd > /dev/null

exit ${feedback}
