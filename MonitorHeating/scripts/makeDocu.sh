#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null
cd ..

mkdir -p docu
mkdir -p tmp
doxygen doxyfile

cd docu/latex
make 2>&1 >> ../../tmp/latex.log

# Back to the original location
popd > /dev/null