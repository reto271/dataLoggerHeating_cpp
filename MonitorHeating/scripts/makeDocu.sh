#!/bin/bash

# Change into the script directory
SCRIPTDIR=$(readlink -f $(dirname "$0"))
pushd "${SCRIPTDIR}" > /dev/null
cd ..

../Common/scripts/showSW_Version.sh

rm -rf docu
mkdir -p docu
mkdir -p tmp

cp ../Common/doxyfile .
sed -i 's#__THE_PROJECT_NAME__#Monitor Heating - Read Data from Luxtronik Controller#g' doxyfile
doxygen doxyfile

#cd docu/latex
#make 2>&1 >> ../../tmp/latex.log

# Back to the original location
popd > /dev/null
